/*
  ==============================================================================

    MediumMenu.cpp
    Created: 22 Aug 2021 7:47:02pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setMediumMenuProps(juce::PopupMenu &menu)
{
    menu.addItem(1, "Medium room");
    menu.addItem(2, "Buc-ee's bathroom");
    menu.addItem(3, "Live room");
    menu.addItem(4, "Stairwell");
}
