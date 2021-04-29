/*
  ==============================================================================

    ViatorSlider.h
    Created: 29 Apr 2021 3:03:28pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;

class ViatorSlider : public juce::LookAndFeel_V4 {
    public:

        void drawLinearSlider (Graphics& g, int x, int y, int width,
                                       int height, float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider)
    override
        {
            g.fillAll (slider.findColour
                                   (Slider::backgroundColourId));

            if (style == Slider::LinearBar ||
                            style == Slider::LinearBarVertical)
            {
                Path p;

                if (style == Slider::LinearBarVertical)
                    p.addRectangle ((float) x,
                                        sliderPos, (float) width,
                                        1.0f + height - sliderPos);
                else
                    p.addRectangle ((float) x,
                                        (float) y, sliderPos - x,
                                        (float) height);

                auto baseColour = slider.findColour
             (Slider::rotarySliderFillColourId).withMultipliedSaturation
             (slider.isEnabled () ? 1.0f : 0.5f)
             .withMultipliedAlpha (0.8f);

                g.setColour (baseColour);
                g.fillPath (p);

                auto lineThickness = jmin (15.0f,
                                     jmin (width, height) * 0.45f) * 0.1f;
                g.drawRect (slider.getLocalBounds ().
                                            toFloat (), lineThickness);
            }
            else
            {
                drawLinearSliderBackground (g, x, y, width,
                                  height, sliderPos, minSliderPos,
                                  maxSliderPos, style, slider);
                drawLinearSliderThumb (g, x, y, width,
                                  height, sliderPos, minSliderPos,
                                  maxSliderPos, style, slider);
            }
        }

        void drawLinearSliderThumb (Graphics& g, int x, int y,
                       int width, int height, float sliderPos,
                       float minSliderPos, float maxSliderPos,
                       const Slider::SliderStyle style,
                       Slider& slider) override
        {
            auto sliderRadius = (float)
                             (getSliderThumbRadius (slider) - 2);

            auto isDownOrDragging = slider.isEnabled () &&
                             (slider.isMouseOverOrDragging () ||
                             slider.isMouseButtonDown ());

            auto knobColour = slider.findColour
                          (Slider::thumbColourId).withMultipliedSaturation
                          ((slider.hasKeyboardFocus (false) ||
                          isDownOrDragging) ? 1.3f : 0.9f)
                          .withMultipliedAlpha (slider.isEnabled ()
                          ? 1.0f : 0.7f);

            auto isMouseOver = slider.isMouseOverOrDragging ()
                             && slider.isEnabled ();

                float kx, ky;

                if (style == Slider::LinearVertical)
                {
                    kx = x + width * 0.5f;
                    ky = sliderPos;
                }
                else
                {
                    kx = sliderPos;
                    ky = y + height * 0.5f;
                }

                // Value
                float fontSize = sliderRadius * 1.4f;
                g.setFont (fontSize);

                g.setColour (slider.findColour
                                  (Slider::thumbColourId).withAlpha
                                  (isMouseOver ? 1.0f : 0.7f));
//                g.drawSingleLineText (String
//                                  (slider.getValue ()), kx + fontSize *
//                                  0.67f - sliderRadius, ky + fontSize *
//                                  1.1f - sliderRadius,
//                                  Justification::centred);
            }
    };
