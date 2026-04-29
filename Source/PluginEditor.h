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

// NOTE: juce::Slider::Listener must be added to be able to obtain values from sliders
class MinimalGainPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    MinimalGainPluginAudioProcessorEditor (MinimalGainPluginAudioProcessor&);
    ~MinimalGainPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Declare sliderValueChanged function
    void sliderValueChanged (juce::Slider *slider) override;
    
    // Declare setupSlider function
    void setupSlider(juce::Slider& slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MinimalGainPluginAudioProcessor& audioProcessor;
    
    // Defining sliders
    juce::Slider inputGainKnob, softClipKnob, outputGainKnob;
    
    // Defining slider labels
    juce::Label inputGainLabel, softClipLabel, outputGainLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MinimalGainPluginAudioProcessorEditor)
};
