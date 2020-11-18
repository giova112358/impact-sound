/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ImpactModelAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ImpactModelAudioProcessorEditor (ImpactModelAudioProcessor&);
    ~ImpactModelAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<juce::Slider> volumeSlider, stiffnessSlider, shapeSlider, dissipationSlider;
    std::unique_ptr<juce::Label> volumeLabel, stiffnessLabel, shapeLabel, dissipationLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volAttachment, stiffAttachment, shapeAttachment, dissAttachment;

    std::unique_ptr<juce::TextButton> playButton;

    juce::LookAndFeel_V4 theLFLight;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ImpactModelAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImpactModelAudioProcessorEditor)
};
