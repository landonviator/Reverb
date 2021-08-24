/*
  ==============================================================================

    LV_Menu.h
    Created: 22 Aug 2021 1:33:05am
    Author:  Landon Viator

  ==============================================================================
*/

/*
  ==============================================================================

    LV_Dial.h
    Created: 20 Jul 2021 9:43:18pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

class LV_Menu : public ComboBox
{
public:
    
    LV_Menu()
    {
        setColour(juce::ComboBox::backgroundColourId, juce::Colours::black.withAlpha(0.35f));
        setColour(juce::ComboBox::textColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
        setColour(juce::ComboBox::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
        setColour(juce::ComboBox::arrowColourId, juce::Colours::whitesmoke.darker(1.0f));
        getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black.brighter(0.12));
        getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
        getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::whitesmoke.withAlpha(0.05f));
        
    }
    
private:

    
    
};
}

