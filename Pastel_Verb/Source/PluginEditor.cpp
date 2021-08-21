/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Pastel_VerbAudioProcessorEditor::Pastel_VerbAudioProcessorEditor (Pastel_VerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setUpWindow(audioProcessor);
}

Pastel_VerbAudioProcessorEditor::~Pastel_VerbAudioProcessorEditor()
{
}

//==============================================================================
void Pastel_VerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Image layer from Illustrator
    pluginBackground = juce::ImageCache::getFromMemory(BinaryData::pluginBackground2_png, BinaryData::pluginBackground2_pngSize);
    g.drawImageWithin(pluginBackground, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::RectanglePlacement::stretchToFit);
              
}

void Pastel_VerbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
