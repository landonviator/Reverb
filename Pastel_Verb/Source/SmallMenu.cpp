/*
  ==============================================================================

    SmallMenu.cpp
    Created: 22 Aug 2021 7:46:52pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setSmallMenuProps(juce::PopupMenu &menu)
{
    menu.addItem(1, "Bathroom");
    menu.addItem(2, "Practice Room");
    menu.addItem(3, "Drum Booth");
    menu.addItem(4, "Vocal Booth");
}
