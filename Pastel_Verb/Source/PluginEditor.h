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
class Pastel_VerbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Pastel_VerbAudioProcessorEditor (Pastel_VerbAudioProcessor&);
    ~Pastel_VerbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    /**Set up the UI window size*/
    void setUpWindow(Pastel_VerbAudioProcessor& audioProcessor);
    
    /**Image background*/
    juce::Image pluginBackground;
    
    /**Logo image*/
    juce::Image headerLogo;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Pastel_VerbAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pastel_VerbAudioProcessorEditor)
};
