/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>

// Function to apply same setup to each slider 
void MinimalGainPluginAudioProcessorEditor::setupSlider(juce::Slider& slider)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
        slider.setNumDecimalPlacesToDisplay(2);
        slider.setRotaryParameters(juce::MathConstants<float>::pi * 5 / 4, juce::MathConstants<float>::pi * 11 / 4, true);
        slider.setVelocityBasedMode(true);
        addAndMakeVisible(slider);
    }

//==============================================================================
MinimalGainPluginAudioProcessorEditor::MinimalGainPluginAudioProcessorEditor (MinimalGainPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 700);
    
    // Plugin is NOT resizable. The window holding the plugin may be resizable depending on the DAW.
    setResizable (false, false);
    
    // Input gain slider
    inputGainLabel.setText ("Input Gain", juce::dontSendNotification);
    addAndMakeVisible (inputGainLabel);
    
    setupSlider(inputGainKnob);
    inputGainKnob.addListener(this);
    inputGainKnob.setRange(-60.0, 12.0);
    inputGainKnob.setSkewFactorFromMidPoint(0.0);
    inputGainKnob.setValue(0.0);
    
    // Soft clipping slider
    softClipLabel.setText ("Soft Clipping", juce::dontSendNotification);
    addAndMakeVisible (softClipLabel);
    
    setupSlider(softClipKnob);
    softClipKnob.addListener(this);
    softClipKnob.setRange(0.0, 12.0);
    softClipKnob.setValue(0.0); 
    
    // Output gain slider
    outputGainLabel.setText ("Output Gain", juce::dontSendNotification);
    addAndMakeVisible (outputGainLabel);
    
    setupSlider(outputGainKnob);
    outputGainKnob.addListener(this);
    outputGainKnob.setRange(-12, 12);
    outputGainKnob.setSkewFactorFromMidPoint(0.0);
    outputGainKnob.setValue(0.0);

}

MinimalGainPluginAudioProcessorEditor::~MinimalGainPluginAudioProcessorEditor()
{
    
    
}

//==============================================================================
void MinimalGainPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::aliceblue);
}

void MinimalGainPluginAudioProcessorEditor::resized()
{
    // All of the math for positioning sliders and text
    auto bounds = getLocalBounds();

    int knobWidth = 200;
    int knobHeight = 200;

    int labelHeight = 20;
    int spacingY = 5;

    int numKnobs = 3;
    int totalKnobWidth = numKnobs * knobWidth;
    int spacingX = (bounds.getWidth() - totalKnobWidth) / (numKnobs + 1);

    int knobY = bounds.getHeight() / 2 - knobHeight / 2;
    int labelY = knobY + knobHeight + spacingY;

    int x1 = spacingX;
    int x2 = spacingX * 2 + knobWidth;
    int x3 = spacingX * 3 + knobWidth * 2;

    // Knobs
    inputGainKnob.setBounds(x1, knobY, knobWidth, knobHeight);
    softClipKnob.setBounds(x2, knobY, knobWidth, knobHeight);
    outputGainKnob.setBounds(x3, knobY, knobWidth, knobHeight);
    
    // Center labels below knobs
    inputGainLabel.setBounds(x1, labelY, knobWidth, labelHeight);
    softClipLabel.setBounds(x2, labelY, knobWidth, labelHeight);
    outputGainLabel.setBounds(x3, labelY, knobWidth, labelHeight);
    
    // Sanity check for centering labels bc JUCE formatting can be wonky
    inputGainLabel.setJustificationType(juce::Justification::centred);
    softClipLabel.setJustificationType(juce::Justification::centred);
    outputGainLabel.setJustificationType(juce::Justification::centred);
}

// Reads in values from sliders, which are then sent to be processed in PluginProcessor.cpp
void MinimalGainPluginAudioProcessorEditor::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &inputGainKnob)
    {
        audioProcessor.dbInput = inputGainKnob.getValue();
    }
    
    if (slider == &softClipKnob)
    {
        audioProcessor.dbClipAmount = softClipKnob.getValue();
    }
    
    if (slider == &outputGainKnob)
    {
        audioProcessor.dbOutput = outputGainKnob.getValue();
    }
}
