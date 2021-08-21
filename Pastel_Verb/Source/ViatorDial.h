/*
  ==============================================================================

    ViatorDial.h
    Created: 12 Feb 2021 5:54:44pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/

class ViatorDial : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override{
        
        float diameter = fmin(width, height) * .7;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                        
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(juce::Colour::fromFloatRGBA(0.15, 0.15, 0.15, 1)); //center
        g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0).darker(1.0).darker(0.1), 0, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0).darker(1.0).darker(0.1), 0));
        g.fillEllipse(dialArea);
                        
        g.setColour(juce::Colours::black.withAlpha(0.15f)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 10.0f);
        juce::Path dialTick;
        g.setColour(juce::Colours::whitesmoke.darker(0.5)); //tick color
        dialTick.addRectangle(0, -radius + 6, 3.0f, radius * 0.6);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
    }
};

class ViatorDial2 : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override{
        
        float diameter = fmin(width, height) * 0.7;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::palevioletred.darker(1.0).darker(0.1), radius, juce::Colours::palevioletred.darker(1.0).darker(0.15), diameter));
        g.fillEllipse(dialArea);
                
        g.setColour(juce::Colours::grey.darker(0.5)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 3.0f);
        juce::Path dialTick;
        g.setColour(juce::Colours::whitesmoke.darker(1.0f)); //tick color
        dialTick.addRectangle(0, -radius + 2, 3.0f, radius * 0.6);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
    }
};
