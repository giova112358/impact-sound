//--------//--------//--------//--------//--------//--------//--------//--------
/*
  ==============================================================================

   This file follows the same open source licensing as the JUCE library.
   Copyright (c) 2016 John Flynn

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   Judio is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ==============================================================================
*/
//--------//--------//--------//--------//--------//--------//--------//--------

#include "State.h"

//#include "Look.h"

namespace jdo
{

    //==============================================================================
    void saveStateToXml(const juce::OwnedArray<juce::AudioProcessorParameter>& params, juce::XmlElement& xml)
    {
        xml.removeAllAttributes(); // clear first

        for (const auto& param : params)
            if (auto* p = dynamic_cast<juce::AudioProcessorParameterWithID*> (param))
                xml.setAttribute(p->paramID, p->getValue()); // 0to1
    }

    void loadStateFromXml(const juce::XmlElement& xml, juce::OwnedArray<juce::AudioProcessorParameter>& params)
    {
        for (const auto& param : params)
            if (auto* p = dynamic_cast<juce::AudioProcessorParameterWithID*> (param))
                // if not in xml set current
                p->setValueNotifyingHost((float)xml.getDoubleAttribute(p->paramID, p->getValue()));
    }

    //==============================================================================
    bool createFileIfNonExistant(const juce::File& file) // returns true if file didn't exist
    {
        if (!file.exists())
        {
            file.create();
            return true;
        }
        jassert(file.exists());
        return false;
    }

    void parseStringToXmlElement(const juce::String& string, juce::XmlElement& xml)                // what could go wrong here?
    {
        juce::ScopedPointer<juce::XmlElement> parsed{ juce::XmlDocument::parse(string).get() };
        if (parsed)
            xml = *parsed;
    }

    void parseFileToXmlElement(const juce::File& file, juce::XmlElement& xml)                  // what could go wrong here?
    {
        juce::ScopedPointer<juce::XmlElement> parsed{ juce::XmlDocument::parse(file).get() };
        if (parsed)
            xml = *parsed;
    }

    void writeXmlElementToFile(const juce::XmlElement& xml, juce::File& file)
    {
        createFileIfNonExistant(file);
        xml.writeToFile(file, "");         // "" is DTD (unused)
    }

    juce::String getNextAvailablePresetID(const juce::XmlElement& presetXml)
    {
        int newPresetIDNumber = presetXml.getNumChildElements() + 1; // 1 indexed to match ComboBox
        return "preset" + static_cast<juce::String> (newPresetIDNumber);   // format: preset##
    }

    //==============================================================================
    StatePresets::StatePresets(juce::OwnedArray<juce::AudioProcessorParameter>& params, const juce::String& presetFileLocation)
        : parameters{ params },
        presetFile{ juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
                                              .getChildFile(presetFileLocation) }
    {
        parseStringToXmlElement(juce::String(defaultPresetsString), defaultPresetsXml);
        parseFileToXmlElement(presetFile, presetXml);

        if (createFileIfNonExistant(presetFile))
            writeXmlElementToFile(defaultPresetsXml, presetFile);
    }

    void StatePresets::loadPreset(int presetID)
    {
        if (1 <= presetID && presetID <= presetXml.getNumChildElements()) // 1 indexed to match ComboBox
        {
            juce::XmlElement loadThisChild{ *presetXml.getChildElement(presetID - 1) }; // (0 indexed method)
            loadStateFromXml(loadThisChild, parameters);
        }
        // else do nothing, on preset delete, refreshing will try to load a non-existent presetID

        currentPresetID = presetID; // allow 0 for 'no preset selected' (?)
    }

    void StatePresets::savePresetToDisk(const juce::String& presetName)
    {
        juce::String newPresetID = getNextAvailablePresetID(presetXml); // presetID format: "preset##"

        juce::ScopedPointer<juce::XmlElement> currentState{ new juce::XmlElement {newPresetID} };  // must be pointer as
        saveStateToXml(parameters, *currentState);                        // parent takes ownership
        currentState->setAttribute("presetName", presetName);

        presetXml.addChildElement(currentState.release());                     // will be deleted by parent element

        writeXmlElementToFile(presetXml, presetFile);  // write changes to shared file on disk
    }

    void StatePresets::deletePresetFromDisk()
    {
        juce::XmlElement* childToDelete{ presetXml.getChildElement(currentPresetID - 1) };
        if (childToDelete)
            presetXml.removeChildElement(childToDelete, true);

        writeXmlElementToFile(presetXml, presetFile);  // write changes to shared file on disk
    }

    juce::StringArray StatePresets::getPresetNamesFromDisk()
    {
        /*return juce::StringArray();*/
        parseFileToXmlElement(presetFile, presetXml); // refresh from disk

        juce::StringArray names;

        forEachXmlChildElement(presetXml, child)                                    // should avoid macro?
        {
            juce::String n = child->getStringAttribute("presetName");
            if (n == "")
                n = "(Unnamed preset)";
            names.add(n);
        }

        return names; // hopefully moves
    }

    int StatePresets::getNumPresets() const
    {
        return presetXml.getNumChildElements();
    }

    int StatePresets::getCurrentPresetId() const
    {
        return currentPresetID;
    }

    //==============================================================================
    void populateComboBox(juce::ComboBox& comboBox, const juce::StringArray& listItems)
    {
        for (int i = 0; i < listItems.size(); ++i)
            comboBox.addItem(listItems[i], i + 1); // 1-indexed ID for ComboBox
    }

    //==============================================================================
    StateComponent::StateComponent(/*StateAB& sab, */StatePresets& sp)
        : /*procStateAB{ sab },*/
        procStatePresets{ sp },
        toggleABButton{ "A-B" },
        copyABButton{ "Copy" },
        presetBox{ "PresetBoxID", this },
        savePresetButton{ "Save" },
        deletePresetButton{ "Delete" }
    {
        addAndMakeVisible(toggleABButton);
        addAndMakeVisible(copyABButton);
        toggleABButton.addListener(this);
        copyABButton.addListener(this);

        addAndMakeVisible(presetBox);
        presetBox.setTextWhenNothingSelected("Load preset...");
        refreshPresetBoxFromDisk();
        ifPresetActiveShowInBox();
        presetBox.addListener(this);

        addAndMakeVisible(savePresetButton);
        savePresetButton.addListener(this);
        addAndMakeVisible(deletePresetButton);
        deletePresetButton.addListener(this);
    }

    void StateComponent::paint(juce::Graphics& /*g*/)
    {
    }

    void StateComponent::resized()
    {
        const int sideBorder{ 20 };
        const int spacer{ 5 };

        juce::Rectangle<int> r(getLocalBounds());                // preset and state bar (explicit juce:: for MSVC2013)

        r.removeFromTop(77);
        r.removeFromLeft(sideBorder);
        r.removeFromRight(sideBorder);
        r.removeFromBottom(r.getHeight() - 22);

        toggleABButton.setBounds(r.removeFromLeft(55));
        r.removeFromLeft(spacer);
        copyABButton.setBounds(r.removeFromLeft(55));

        deletePresetButton.setBounds(r.removeFromRight(55));
        r.removeFromRight(spacer);
        presetBox.setBounds(r.removeFromRight(55 * 4));
        r.removeFromRight(spacer);
        savePresetButton.setBounds(r.removeFromRight(55));
    }

    void StateComponent::buttonClicked(juce::Button* clickedButton)
    {
        /*if (clickedButton == &toggleABButton)     procStateAB.toggleAB();
        if (clickedButton == &copyABButton)       procStateAB.copyAB();*/
        if (clickedButton == &savePresetButton)   savePresetAlertWindow();
        if (clickedButton == &deletePresetButton) deletePresetAndRefresh();
    }

    void StateComponent::comboBoxChanged(juce::ComboBox* changedComboBox)
    {
        const int selectedId{ changedComboBox->getSelectedId() };
        procStatePresets.loadPreset(selectedId);
    }

    void StateComponent::refreshPresetBoxFromDisk()
    {
        presetBox.clear();
        juce::StringArray presetNames{ procStatePresets.getPresetNamesFromDisk() };

        juce::StringArray empty = juce::StringArray();

        if (presetNames != empty)
            populateComboBox(presetBox, presetNames);
        else
            presetBox.getRootMenu()->addItem(1, "No presets", false, false);
    }

    void StateComponent::ifPresetActiveShowInBox()
    {
        const int currentPreset{ procStatePresets.getCurrentPresetId() };
        const int numPresets{ procStatePresets.getNumPresets() };
        if (1 <= currentPreset && currentPreset <= numPresets)
            presetBox.setSelectedId(currentPreset, juce::dontSendNotification);
    }

    void StateComponent::deletePresetAndRefresh()
    {
        procStatePresets.deletePresetFromDisk();
        refreshPresetBoxFromDisk();
    }

    void StateComponent::savePresetAlertWindow()
    {
        enum choice { ok, cancel };

        juce::AlertWindow alert{ "Save preset...", "", juce::AlertWindow::AlertIconType::NoIcon };
        alert.addTextEditor("presetEditorID", "Enter preset name");
        alert.addButton("OK", choice::ok, juce::KeyPress(juce::KeyPress::returnKey, 0, 0));
        alert.addButton("Cancel", choice::cancel, juce::KeyPress(juce::KeyPress::escapeKey, 0, 0));

        if (alert.runModalLoop() == choice::ok)                                     // LEAKS when quit while open !!!
        {
            juce::String presetName{ alert.getTextEditorContents("presetEditorID") };

            procStatePresets.savePresetToDisk(presetName);
            refreshPresetBoxFromDisk();
            presetBox.setSelectedId(procStatePresets.getNumPresets());
        }
    }

    void StateComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
    {
        refreshPresetBoxFromDisk();
    }

} // namespace jdo