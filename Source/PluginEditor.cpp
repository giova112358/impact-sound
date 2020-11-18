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

    /*velocitySlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(velocitySlider.get());
    velAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VEL", *velocityLabel);
    velocityLabel = std::make_unique<juce::Label>("", "Velocity");
    addAndMakeVisible(velocityLabel.get());
    velocityLabel->attachToComponent(velocitySlider.get(), false);
    velocityLabel->setJustificationType(juce::Justification::centredBottom);

    massSlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(massSlider.get());
    massAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MASS", *massSlider);
    massLabel = std::make_unique<juce::Label>("", "Mass");
    addAndMakeVisible(massLabel.get());
    massLabel->attachToComponent(massSlider.get(), false);
    massLabel->setJustificationType(juce::Justification::centredBottom);

    forceSlider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(forceSlider.get());
    forceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FOR", *forceSlider);
    forceLabel = std::make_unique<juce::Label>("", "Force");
    addAndMakeVisible(forceLabel.get());
    forceLabel->attachToComponent(forceSlider.get(), false);
    forceLabel->setJustificationType(juce::Justification::centredBottom);

    freq0Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(freq0Slider.get());
    freq0Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ0", *freq0Slider);
    freq0Label = std::make_unique<juce::Label>("", "Frequency 0");
    addAndMakeVisible(freq0Label.get());
    freq0Label->attachToComponent(freq0Slider.get(), false);
    freq0Label->setJustificationType(juce::Justification::centredBottom);

    freq1Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(freq1Slider.get());
    freq1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ1", *freq1Slider);
    freq1Label = std::make_unique<juce::Label>("", "Frequency 1");
    addAndMakeVisible(forceLabel.get());
    freq1Label->attachToComponent(freq1Slider.get(), false);
    freq1Label->setJustificationType(juce::Justification::centredBottom);

    freq2Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(freq2Slider.get());
    freq2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ2", *freq2Slider);
    freq2Label = std::make_unique<juce::Label>("", "Frequency 2");
    addAndMakeVisible(forceLabel.get());
    freq2Label->attachToComponent(freq2Slider.get(), false);
    freq2Label->setJustificationType(juce::Justification::centredBottom);

    decay0Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(decay0Slider.get());
    decay0Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEC0", *decay0Slider);
    decay0Label = std::make_unique<juce::Label>("", "Decay 0");
    addAndMakeVisible(decay0Label.get());
    decay0Label->attachToComponent(decay0Slider.get(), false);
    decay0Label->setJustificationType(juce::Justification::centredBottom);

    decay1Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(decay1Slider.get());
    decay1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEC1", *decay1Slider);
    decay1Label = std::make_unique<juce::Label>("", "Decay 1");
    addAndMakeVisible(decay1Label.get());
    decay1Label->attachToComponent(decay1Slider.get(), false);
    decay1Label->setJustificationType(juce::Justification::centredBottom);

    decay2Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(decay2Slider.get());
    decay2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEC2", *decay2Slider);
    decay2Label = std::make_unique<juce::Label>("", "Decay 2");
    addAndMakeVisible(decay2Label.get());
    decay2Label->attachToComponent(decay2Slider.get(), false);
    decay2Label->setJustificationType(juce::Justification::centredBottom);

    gain10Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(gain10Slider.get());
    gain10Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAINPICK10", *gain10Slider);
    gain10Label = std::make_unique<juce::Label>("", "Gain Pickup1 Mode0");
    addAndMakeVisible(gain10Label.get());
    gain10Label->attachToComponent(gain10Slider.get(), false);
    gain10Label->setJustificationType(juce::Justification::centredBottom);

    gain11Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(gain11Slider.get());
    gain11Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAINPICK11", *gain11Slider);
    gain11Label = std::make_unique<juce::Label>("", "Gain Pickup1 Mode1");
    addAndMakeVisible(gain11Label.get());
    gain11Label->attachToComponent(gain11Slider.get(), false);
    gain11Label->setJustificationType(juce::Justification::centredBottom);

    gain12Slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow);
    addAndMakeVisible(gain12Slider.get());
    gain11Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAINPICK12", *gain12Slider);
    gain11Label = std::make_unique<juce::Label>("", "Gain Pickup1 Mode2");
    addAndMakeVisible(gain12Label.get());
    gain12Label->attachToComponent(gain12Slider.get(), false);
    gain12Label->setJustificationType(juce::Justification::centredBottom);*/

    playButton = std::make_unique<juce::TextButton>("Play");
    playButton.get()->onClick = [this]() { audioProcessor.strike(); };
    addAndMakeVisible(playButton.get());

    theLFLight.setColourScheme(juce::LookAndFeel_V4::getLightColourScheme());
    juce::LookAndFeel::setDefaultLookAndFeel(&theLFLight);

    setSize(4000, 300);
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
    //grid.items.add((juce::GridItem(massSlider.get())));
    //grid.items.add((juce::GridItem(velocitySlider.get())));
    //grid.items.add((juce::GridItem(forceSlider.get())));
    //grid.items.add((juce::GridItem(freq0Slider.get())));
    //grid.items.add((juce::GridItem(freq1Slider.get())));
    //grid.items.add((juce::GridItem(freq2Slider.get())));
    //grid.items.add((juce::GridItem(decay0Slider.get())));
    //grid.items.add((juce::GridItem(decay1Slider.get())));
    //grid.items.add((juce::GridItem(decay2Slider.get())));
    //grid.items.add((juce::GridItem(gain10Slider.get())));
    //grid.items.add((juce::GridItem(gain11Slider.get())));
    //grid.items.add((juce::GridItem(gain12Slider.get())));
    grid.items.add((juce::GridItem(stiffnessSlider.get())));
    grid.items.add((juce::GridItem(shapeSlider.get())));
    grid.items.add((juce::GridItem(dissipationSlider.get())));
    grid.items.add(juce::GridItem(volumeSlider.get()).withSize(300, 20));
    

    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1))
    ,Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) 
    , Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };
    grid.templateRows = { Track(Fr(1)) };
    grid.columnGap = juce::Grid::Px(10);
    grid.rowGap = juce::Grid::Px(50);

    grid.performLayout(bounds);
}
