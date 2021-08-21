/*
  ==============================================================================

    FilterEngageButton.cpp
    Created: 21 Aug 2021 2:12:18am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setSetFilterEngageButtonProps(juce::TextButton &button)
{
    button.setButtonText("In");
        
    //enabledToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, eqToggleId, enabledToggle);

    const auto message = button.getToggleState() ? "In" : "Out";

    button.setButtonText(message);

    button.onClick = [&]()
    {
        const auto message = button.getToggleState() ? "In" : "Out";

        button.setButtonText(message);
    };
}
