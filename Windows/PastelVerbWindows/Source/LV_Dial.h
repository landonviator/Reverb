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

class LV_Dial : public Slider
{
public:
    
    LV_Dial()
    {
        setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
        setTextBoxStyle(Slider::TextBoxBelow, false, 72, 32);
        setRange(-24.0, 24.0, 0.25);
        setDoubleClickReturnValue(true, 0.0);
        setTextValueSuffix(" dB");
        setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(Slider::ColourIds::thumbColourId));
        setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colour::fromRGB(35, 35, 35));
        setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black.withAlpha(0.0f));
        setColour(Slider::ColourIds::textBoxTextColourId, Colours::whitesmoke.withAlpha(0.25f));
    }
    
private:

    
    
};
}