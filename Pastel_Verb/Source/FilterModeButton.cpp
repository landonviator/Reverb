/*
  ==============================================================================

    FilterModeButton.cpp
    Created: 21 Aug 2021 2:12:02am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setSetFilterModeButtonProps(juce::TextButton &button)
{
    // Individual button props
    button.setColour(0x1000100, juce::Colours::lightgoldenrodyellow.darker(0.2f));
    button.setColour(0x1000102, juce::Colours::black.brighter(0.1));
    button.setButtonText("12 dB/Oct");
        
    //enabledToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, eqToggleId, enabledToggle);

    // Change the button text based on the state
    const auto message = button.getToggleState() ? "12 dB/Oct" : "24 dB/Oct";

    button.setButtonText(message);

    button.onClick = [&]()
    {
        const auto message = button.getToggleState() ? "12 dB/Oct" : "24 dB/Oct";

        button.setButtonText(message);
    };
}
