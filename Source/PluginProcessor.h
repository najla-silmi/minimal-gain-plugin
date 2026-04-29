/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MinimalGainPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MinimalGainPluginAudioProcessor();
    ~MinimalGainPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float dbInput; // dB input
    float dbOutput; // dB output
    
    float inGain; // Linear input gain factor
    float outGain; // Linear output gain factor
    
    juce::SmoothedValue<float> inGainSmoothed;
    juce::SmoothedValue<float> outGainSmoothed;
    juce::SmoothedValue<float> clipAmountSmoothed;
    
    float dbClipAmount; // Clip amount in dB
    float clipAmount; // Clip amount converted from dB

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MinimalGainPluginAudioProcessor)
};
