/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MinimalGainPluginAudioProcessor::MinimalGainPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MinimalGainPluginAudioProcessor::~MinimalGainPluginAudioProcessor()
{
}

//==============================================================================
const juce::String MinimalGainPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MinimalGainPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MinimalGainPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MinimalGainPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MinimalGainPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MinimalGainPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MinimalGainPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MinimalGainPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MinimalGainPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void MinimalGainPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MinimalGainPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Parameter smoothing to prevent zipper noise (20ms)
    // Not too fast, but enough to avoid noticeable stepping
    inGainSmoothed.reset(sampleRate, 0.02);  
    outGainSmoothed.reset(sampleRate, 0.02);
    clipAmountSmoothed.reset(sampleRate, 0.02);
}

void MinimalGainPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MinimalGainPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MinimalGainPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Convert parameters from dB to linear gain factors
    inGain = juce::Decibels::decibelsToGain(dbInput);
    outGain = juce::Decibels::decibelsToGain(dbOutput);
    clipAmount = juce::Decibels::decibelsToGain(dbClipAmount);

    // Set smoothing targets
    inGainSmoothed.setTargetValue(inGain);
    outGainSmoothed.setTargetValue(outGain);
    clipAmountSmoothed.setTargetValue(clipAmount);

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float inGainFinal = inGainSmoothed.getNextValue();
        float outGainFinal = outGainSmoothed.getNextValue();
        float drive = std::max(0.001f, clipAmountSmoothed.getNextValue()); // Prevents drive from hitting 0

        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            float& sample = channelData[i];

            sample *= inGainFinal;

            // Normalized soft clipping using tanh, a type of gradual saturation
            sample = std::tanh(sample * drive) / std::tanh(drive); 

            sample *= outGainFinal;
        }
    }
}

//==============================================================================
bool MinimalGainPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MinimalGainPluginAudioProcessor::createEditor()
{
    return new MinimalGainPluginAudioProcessorEditor (*this);
}

//==============================================================================
void MinimalGainPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void MinimalGainPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MinimalGainPluginAudioProcessor();
}
