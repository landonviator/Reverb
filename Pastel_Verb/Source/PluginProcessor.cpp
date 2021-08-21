/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Pastel_VerbAudioProcessor::Pastel_VerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
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
    
    variableTree = {
                    
                    "ReverbVariables", {},
                    {
                      { "Group", {{ "name", "ReverbVars" }},
                        {
                          { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                            { "Parameter", {{ "id", "height" }, { "value", 0.0 }}},
                        }
                      }
                    }
                  };
    
    
}

Pastel_VerbAudioProcessor::~Pastel_VerbAudioProcessor()
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
const juce::String Pastel_VerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Pastel_VerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Pastel_VerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Pastel_VerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Pastel_VerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Pastel_VerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Pastel_VerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Pastel_VerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Pastel_VerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void Pastel_VerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Pastel_VerbAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    params.reserve(10);
    
    auto filterEngageParam = std::make_unique<juce::AudioParameterInt>(filterEngageId, filterEngageName, 0, 1, 1);
    auto filterModeParam = std::make_unique<juce::AudioParameterInt>(filterModeId, filterModeName, 0, 1, 0);
    auto cutoffParam = std::make_unique<juce::AudioParameterInt>(cutoffSliderId, cutoffSliderName, 20, 20000, 1200);
    auto resonanceParam = std::make_unique<juce::AudioParameterInt>(resonanceSliderId, resonanceSliderName, 0, 100, 0);
    auto driveParam = std::make_unique<juce::AudioParameterFloat>(driveSliderId, driveSliderName, 0.0f, 24.0f, 0.0f);
    auto roomSizeParam = std::make_unique<juce::AudioParameterInt>(roomSizeSliderId, roomSizeSliderName, 0, 100, 50);
    auto dampingParam = std::make_unique<juce::AudioParameterInt>(dampingSliderId, dampingSliderName, 0, 100, 50);
    auto widthParam = std::make_unique<juce::AudioParameterInt>(widthSliderId, widthSliderName, 0, 100, 100);
    auto dryParam = std::make_unique<juce::AudioParameterInt>(drySliderId, drySliderName, 0, 100, 0);
    auto wetParam = std::make_unique<juce::AudioParameterInt>(wetSliderId, wetSliderName, 0, 100, 50);
    
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

void Pastel_VerbAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    if (parameterID == cutoffSliderId)
    {
        //ladderProcessor.setCutoffFrequencyHz(newValue);
        DBG("Cutoff " << newValue);
    }
    
    else if (parameterID == resonanceSliderId)
    {
        //ladderProcessor.setResonance(newValue * 0.01);
        DBG("Resonance " << newValue);
    }
    
    else if (parameterID == driveSliderId)
    {
        //ladderProcessor.setDrive(pow(10, newValue / 20));
        DBG("Drive " << newValue);
    }
    
    else if (parameterID == filterEngageId)
    {
        if (newValue == 0)
        {
            //ladderProcessor.setEnabled(false);
            DBG("Filter off");
        }
        
        else
        {
            //ladderProcessor.setEnabled(true);
            DBG("Filter on");
        }
    }
    
    else if (parameterID == filterModeId)
    {
        if (newValue == 0)
        {
            //ladderProcessor.setMode(juce::dsp::LadderFilterMode::LPF12);
            DBG("Filter mode " << newValue);
        }
        
        else
        {
            //ladderProcessor.setMode(juce::dsp::LadderFilterMode::LPF24);
            DBG("Filter mode " << newValue);
        }
    }
    
    else if (parameterID == wetSliderId)
    {
        //reverbParams.wetLevel = newValue * 0.01;
        //reverbProcessor.setParameters(reverbParams);
        DBG("Wet " << newValue);
    }
    
    else if (parameterID == drySliderId)
    {
        //reverbParams.dryLevel = newValue * 0.01;
        //reverbProcessor.setParameters(reverbParams);
        DBG("Dry " << newValue);
    }
    
    else if (parameterID == roomSizeSliderId)
    {
        //reverbParams.roomSize = newValue * 0.01;
        //reverbProcessor.setParameters(reverbParams);
        DBG("Room " << newValue);
    }
    
    else if (parameterID == dampingSliderId)
    {
        //reverbParams.damping = newValue * 0.01;
        //reverbProcessor.setParameters(reverbParams);
        DBG("Damping " << newValue);
    }
    
    else
    {
        //reverbParams.width = newValue * 0.01;
        //reverbProcessor.setParameters(reverbParams);
        DBG("Width " << newValue);
    }
}

//==============================================================================
void Pastel_VerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Pastel_VerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Pastel_VerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Pastel_VerbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
bool Pastel_VerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Pastel_VerbAudioProcessor::createEditor()
{
    return new Pastel_VerbAudioProcessorEditor (*this);
}

//==============================================================================
void Pastel_VerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    treeState.state.appendChild(variableTree, nullptr);

    juce::MemoryOutputStream stream(destData, false);
    
    treeState.state.writeToStream (stream);
}

void Pastel_VerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData (data, size_t (sizeInBytes));
        
    variableTree = tree.getChildWithName("ReverbVariables");

    if (tree.isValid())
    {
        treeState.state = tree;
    }
    
    windowWidth = variableTree.getProperty("width");
    windowHeight = variableTree.getProperty("height");
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Pastel_VerbAudioProcessor();
}
