/*
  ==============================================================================

    InitSliders.cpp
    Created: 20 Aug 2021 9:48:15pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::initSliders()
{
    for (auto i {0}; i < sliders.size(); i++)
    {
        addAndMakeVisible(sliders[i]);
    }
}
