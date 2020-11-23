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

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <JuceHeader.h>

//#include "Slider.h"
//#include "Parameter.h"

namespace jdo
{

    //==============================================================================
    /** For all methods below that require a non-const OwnedArray<AudioProcessorParameter>&
        remember to make a...
            OwnedArray<AudioProcessorParameter>& getParametersForWriting();
        ...function in your derived PluginProcessor class, which just casts away const
        on AudioProcessor::getParameters()
    */
    void saveStateToXml(const juce::OwnedArray<juce::AudioProcessorParameter>& params, juce::XmlElement& xml);
    void loadStateFromXml(const juce::XmlElement& xml, juce::OwnedArray<juce::AudioProcessorParameter>& params);

    //==============================================================================
    bool createFileIfNonExistant(const juce::File& file);
    void parseFileToXmlElement(const juce::File& file, juce::XmlElement& xml);
    void writeXmlElementToFile(const juce::XmlElement& xml, juce::File& file);
    juce::String getNextAvailablePresetID(const juce::XmlElement& presetXml);

    //==============================================================================
    /** Create StatePresets object with XML file saved relative to user
        data directory.
        e.g. StatePresets my_sps {"JohnFlynnPlugins/ThisPlugin/presets.xml"}
        Full path Mac  = ~/Library/JohnFlynnPlugins/ThisPlugin/presets.xml
    */
    class StatePresets
    {
    public:
        StatePresets(juce::OwnedArray<juce::AudioProcessorParameter>& params, const juce::String& presetFileLocation);
        ~StatePresets() {}

        void loadPreset(int presetID);

        void savePresetToDisk(const juce::String& presetName);
        void deletePresetFromDisk();
        juce::StringArray getPresetNamesFromDisk();

        int getNumPresets() const;
        int getCurrentPresetId() const;

    private:
        juce::OwnedArray<juce::AudioProcessorParameter>& parameters;
        juce::XmlElement presetXml{ "PRESETS" }; // local, in-plugin representation
        juce::File presetFile;                  // on-disk representation
        int currentPresetID{ 0 };

        juce::String defaultPresetsString{ juce::String(BinaryData::presets_xml) };
        juce::XmlElement defaultPresetsXml{ "DEFAULTPRESETS" };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StatePresets)
    };

    //==============================================================================
    /** We need to reload the presets from disk every time the mouse drops down the
        combobox. (This syncs changes from other plugin instances)

        We need to call refreshPresetBoxFromDisk() which is a member of the parent.
        This sends a callback up the stack which is caught by the parent.

        NOT a very elegant solution!!!
    */
    class ComboBoxWithRefreshOnClick : public juce::ComboBox,
        public juce::ChangeBroadcaster
    {
    public:
        ComboBoxWithRefreshOnClick(const juce::String& componentName, juce::ChangeListener* parentStateComponent)
            : juce::ComboBox{ componentName }
        {
            addChangeListener(parentStateComponent);
        }

        void showPopup()
        {
            sendSynchronousChangeMessage();
            juce::ComboBox::showPopup();
        }
    };

    //==============================================================================
    /** GUI-side component for the State objects. Handles GUI visual layout and
        logic of the state handlers.

        Make private member of the PluginEditor. Initialise with the StateAB
        and StatePresets objects (these should be public members of the
        PluginProcessor).
    */
    class StateComponent : public juce::Component,
        public juce::Button::Listener,
        public juce::ComboBox::Listener,
        public juce::ChangeListener
    {
    public:
        StateComponent(StatePresets& sp);

        void paint(juce::Graphics&) override;
        void resized() override;

    private:
        StatePresets& procStatePresets;

        juce::TextButton                  toggleABButton;
        juce::TextButton                  copyABButton;
        ComboBoxWithRefreshOnClick  presetBox;
        juce::TextButton                  savePresetButton;
        juce::TextButton                  deletePresetButton;

        void buttonClicked(juce::Button* clickedButton) override;
        void comboBoxChanged(juce::ComboBox* changedComboBox) override;

        void refreshPresetBoxFromDisk();
        void ifPresetActiveShowInBox();
        void deletePresetAndRefresh();
        void savePresetAlertWindow();

        void changeListenerCallback(juce::ChangeBroadcaster* source) override; // refresh presetBox from disk on click

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateComponent)
    };

    //==============================================================================
} // namespace jdo

#endif  // STATE_H_INCLUDED