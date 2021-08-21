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
    
    // Draw and position the image
    g.drawImageWithin(pluginBackground, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::RectanglePlacement::stretchToFit);
    
    // Logo layer
    headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(headerLogo, AudioProcessorEditor::getWidth() * 0.38, AudioProcessorEditor::getHeight() * 0.8 + 4, AudioProcessorEditor::getWidth() * 0.25, AudioProcessorEditor::getHeight() * 0.1, juce::RectanglePlacement::centred);
    
    // Footer text
    // Make sure the text is never too small, which would cause UX issues
    if (AudioProcessorEditor::getWidth() * 0.015 > 9.0)
    {
        g.setFont (AudioProcessorEditor::getWidth() * 0.015);
    }
    
    else
    {
        g.setFont (9.0);
    }
    g.setColour (juce::Colours::whitesmoke.withAlpha(0.25f));
    g.drawFittedText ("Pastel Verb v2.0.0", AudioProcessorEditor::getWidth() * 0.12, AudioProcessorEditor::getHeight() * 0.18, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::Justification::topLeft, 1);
}

void Pastel_VerbAudioProcessorEditor::resized()
{
    // Save plugin size in value tree
    audioProcessor.variableTree.setProperty("width", getWidth(), nullptr);
    audioProcessor.variableTree.setProperty("height", getHeight(), nullptr);
    
    // Save the current size of the window to recall opening the plugin after minimizing it
    // There was a bug where resized() started in the middle of the constructor
    // This was causing it to always open very small
    // This if check fixes it
    if (constructorFinished)
    {
        audioProcessor.windowWidth = AudioProcessorEditor::getWidth();
        audioProcessor.windowHeight = AudioProcessorEditor::getHeight();
    }
}
