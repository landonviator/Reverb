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
    
    initShadows();
    initSliders();
    initButtons();
    initLabels();
}

Pastel_VerbAudioProcessorEditor::~Pastel_VerbAudioProcessorEditor()
{
    // Clean up LAF pointers
    for (auto i {0}; i < sliders.size(); i++)
    {
        sliders[i]->setLookAndFeel(nullptr);
    }
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
    // Some helpful variables to map out the bounds
    auto topMargin {AudioProcessorEditor::getHeight() * 0.15};
    auto height {AudioProcessorEditor::getHeight()};
    auto leftMargin {AudioProcessorEditor::getWidth() / 6.0};
    auto buttonWidth {AudioProcessorEditor::getWidth() / 14.0};
    auto dialSize {AudioProcessorEditor::getWidth() / 9};
    auto spaceBetweenDials {1.1};
    auto sliderWidth {dialSize};
    auto sliderHeight {dialSize * 2.32};
    
    // The button positions
    filterModeButton.setBounds(leftMargin, topMargin * 2, buttonWidth, buttonWidth / 2);
    filterEngageButton.setBounds(filterModeButton.getX(), filterModeButton.getY() + filterModeButton.getHeight() * 2, buttonWidth, buttonWidth / 2);

    // The dial positions
    cutoffSlider.setBounds(filterModeButton.getX() + filterModeButton.getWidth() * 2, filterModeButton.getY() - filterModeButton.getHeight() * 1.95, dialSize, dialSize);
    roomSizeSlider.setBounds(cutoffSlider.getX(), cutoffSlider.getY() + cutoffSlider.getHeight() + filterModeButton.getHeight(), dialSize, dialSize);
    resonanceSlider.setBounds(cutoffSlider.getX() + cutoffSlider.getWidth(), cutoffSlider.getY(), dialSize, dialSize);
    dampingSlider.setBounds(roomSizeSlider.getX() + roomSizeSlider.getWidth(), roomSizeSlider.getY(), dialSize, dialSize);
    driveSlider.setBounds(resonanceSlider.getX() + resonanceSlider.getWidth(), resonanceSlider.getY(), dialSize, dialSize);
    widthSlider.setBounds(dampingSlider.getX() + dampingSlider.getWidth(), dampingSlider.getY(), dialSize, dialSize);
    drySlider.setBounds(widthSlider.getX() + filterModeButton.getWidth() * 2, driveSlider.getY(), sliderWidth, sliderHeight);
    wetSlider.setBounds(drySlider.getX() + drySlider.getWidth(), drySlider.getY(), drySlider.getWidth(), drySlider.getHeight());
    
    // Save the window size last before resized() finishes to recall it properly at construction
    saveWindowSize();
}
