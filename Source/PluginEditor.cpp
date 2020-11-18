/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ImpactModelAudioProcessorEditor::ImpactModelAudioProcessorEditor (ImpactModelAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    volumeSlider = std::make_unique<juce::Slider >(juce::Slider::SliderStyle::LinearHorizontal, juce::Slider::TextBoxRight);
    addAndMakeVisible(volumeSlider.get());
    volAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VOL", *volumeSlider);

    volumeLabel = std::make_unique<juce::Label>("", "Volume");
    addAndMakeVisible(volumeLabel.get());
    volumeLabel->attachToComponent(volumeSlider.get(), false);
    volumeLabel->setJustificationType(juce::Justification::centredLeft);

    stiffnessSlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(stiffnessSlider.get());
    stiffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "STIFF", *stiffnessSlider);

    stiffnessLabel = std::make_unique<juce::Label>("", "Stiffness");
    addAndMakeVisible(stiffnessLabel.get());
    stiffnessLabel->attachToComponent(stiffnessSlider.get(), false);
    stiffnessLabel->setJustificationType(juce::Justification::centredBottom);

    shapeSlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(shapeSlider.get());
    shapeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SH", *shapeSlider);

    shapeLabel = std::make_unique<juce::Label>("", "Shape");
    addAndMakeVisible(shapeLabel.get());
    shapeLabel->attachToComponent(shapeSlider.get(), false);
    shapeLabel->setJustificationType(juce::Justification::centredBottom);

    dissipationSlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(dissipationSlider.get());
    dissAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DISS", *dissipationSlider);

    dissipationLabel = std::make_unique<juce::Label>("", "Dissipation");
    addAndMakeVisible(dissipationLabel.get());
    dissipationLabel->attachToComponent(dissipationSlider.get(), false);
    dissipationLabel->setJustificationType(juce::Justification::centredBottom);

    playButton = std::make_unique<juce::TextButton>("Play");
    playButton.get()->onClick = [this]() { audioProcessor.strike(); };
    addAndMakeVisible(playButton.get());

    theLFLight.setColourScheme(juce::LookAndFeel_V4::getLightColourScheme());
    juce::LookAndFeel::setDefaultLookAndFeel(&theLFLight);

    setSize(400, 300);
}

ImpactModelAudioProcessorEditor::~ImpactModelAudioProcessorEditor()
{
}

//==============================================================================
void ImpactModelAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ImpactModelAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(10, 10);
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.items.add((juce::GridItem(playButton.get())).withSize(60, 60));
    grid.items.add((juce::GridItem(stiffnessSlider.get())));
    grid.items.add((juce::GridItem(shapeSlider.get())));
    grid.items.add((juce::GridItem(dissipationSlider.get())));
    grid.items.add(juce::GridItem(volumeSlider.get()).withSize(300, 20));
    

    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };
    grid.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    grid.columnGap = juce::Grid::Px(10);
    grid.rowGap = juce::Grid::Px(50);

    grid.performLayout(bounds);
}
