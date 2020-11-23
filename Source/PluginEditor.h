/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "State.h"

//==============================================================================
/**
*/
class ImpactModelAudioProcessorEditor  : public juce::AudioProcessorEditor, 
    public juce::Button::Listener
{
public:
    ImpactModelAudioProcessorEditor (ImpactModelAudioProcessor&);
    ~ImpactModelAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void buttonClicked(juce::Button* button) override;

private:
    std::unique_ptr<juce::Slider> volumeSlider, stiffnessSlider, shapeSlider, dissipationSlider, 
        velocitySlider, massSlider, forceSlider, freq0Slider, freq1Slider, freq2Slider, decay0Slider,
        decay1Slider, decay2Slider, gain10Slider, gain11Slider, gain12Slider;

    std::unique_ptr<juce::Label> volumeLabel, stiffnessLabel, shapeLabel, dissipationLabel, velocityLabel,
        massLabel, forceLabel, freq0Label, freq1Label, freq2Label, decay0Label, decay1Label, decay2Label,
        gain10Label, gain11Label, gain12Label;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volAttachment, stiffAttachment, 
        shapeAttachment, dissAttachment, velAttachment, massAttachment, forceAttachment, freq0Attachment, 
        freq1Attachment, freq2Attachment, decay0Attachment, decay1Attachment, decay2Attachment, gain10Attachment,
        gain11Attachment, gain12Attachment;

    std::unique_ptr<juce::TextButton> playButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> playAttachment;

    std::unique_ptr<juce::TextButton> presButton;
    int currentPres = 1;

    /*jdo::StateComponent stateComponent;*/

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ImpactModelAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImpactModelAudioProcessorEditor)
};
