/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessor::ReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), false)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
    treeState.addParameterListener (filterEngageId, this);
    treeState.addParameterListener (filterModeId, this);
    treeState.addParameterListener (cutoffSliderId, this);
    treeState.addParameterListener (resonanceSliderId, this);
    treeState.addParameterListener (driveSliderId, this);
    treeState.addParameterListener (roomSizeSliderId, this);
    treeState.addParameterListener (dampingSliderId, this);
    treeState.addParameterListener (widthSliderId, this);
    treeState.addParameterListener (drySliderId, this);
    treeState.addParameterListener (wetSliderId, this);
}

ReverbAudioProcessor::~ReverbAudioProcessor()
{
    treeState.removeParameterListener (filterEngageId, this);
    treeState.removeParameterListener (filterModeId, this);
    treeState.removeParameterListener (cutoffSliderId, this);
    treeState.removeParameterListener (resonanceSliderId, this);
    treeState.removeParameterListener (driveSliderId, this);
    treeState.removeParameterListener (roomSizeSliderId, this);
    treeState.removeParameterListener (dampingSliderId, this);
    treeState.removeParameterListener (widthSliderId, this);
    treeState.removeParameterListener (drySliderId, this);
    treeState.removeParameterListener (wetSliderId, this);
}

//==============================================================================
const juce::String ReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool ReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReverbAudioProcessor::createEditor()
{
    return new ReverbAudioProcessorEditor (*this);
}

//==============================================================================
void ReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void ReverbAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    
    
}

juce::AudioProcessorValueTreeState::ParameterLayout ReverbAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    params.reserve(10);
    
    auto filterEngageParam = std::make_unique<juce::AudioParameterInt>(filterEngageId, filterEngageName, 0, 1, 0);
    auto filterModeParam = std::make_unique<juce::AudioParameterInt>(filterModeId, filterModeName, 0, 1, 0);
    auto cutoffParam = std::make_unique<juce::AudioParameterFloat>(cutoffSliderId, cutoffSliderName, 20.0f, 20000.0f, 20000.0f);
    auto resonanceParam = std::make_unique<juce::AudioParameterFloat>(resonanceSliderId, resonanceSliderName, 0.0f, 100.0f, 0.0f);
    auto driveParam = std::make_unique<juce::AudioParameterFloat>(driveSliderId, driveSliderName, 0.0f, 24.0f, 0.0f);
    auto roomSizeParam = std::make_unique<juce::AudioParameterFloat>(roomSizeSliderId, roomSizeSliderName, 0.0f, 100.0f, 0.0f);
    auto dampingParam = std::make_unique<juce::AudioParameterFloat>(dampingSliderId, dampingSliderName, 0.0f, 100.0f, 0.0f);
    auto widthParam = std::make_unique<juce::AudioParameterFloat>(widthSliderId, widthSliderName, 0.0f, 100.0f, 0.0f);
    auto dryParam = std::make_unique<juce::AudioParameterFloat>(drySliderId, drySliderName, 0.0f, 100.0f, 0.0f);
    auto wetParam = std::make_unique<juce::AudioParameterFloat>(wetSliderId, wetSliderName, 0.0f, 100.0f, 0.0f);
    
    params.push_back(std::move(filterEngageParam));
    params.push_back(std::move(filterModeParam));
    params.push_back(std::move(cutoffParam));
    params.push_back(std::move(resonanceParam));
    params.push_back(std::move(driveParam));
    params.push_back(std::move(roomSizeParam));
    params.push_back(std::move(dampingParam));
    params.push_back(std::move(widthParam));
    params.push_back(std::move(dryParam));
    params.push_back(std::move(wetParam));
    
    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbAudioProcessor();
}
