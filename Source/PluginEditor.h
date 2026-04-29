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
    
    void sliderValueChanged (juce::Slider *slider) override;
  
    void setupSlider(juce::Slider& slider);

private:
    MinimalGainPluginAudioProcessor& audioProcessor;
    
    juce::Slider inputGainKnob, softClipKnob, outputGainKnob;
    
    juce::Label inputGainLabel, softClipLabel, outputGainLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MinimalGainPluginAudioProcessorEditor)
};
