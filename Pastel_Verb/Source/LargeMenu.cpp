/*
  ==============================================================================

    LargeMenu.cpp
    Created: 22 Aug 2021 7:47:12pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setLargeMenuProps(juce::PopupMenu &menu)
{
    menu.addItem(1, "Cathedral");
    menu.addItem(2, "Aircraft Hanger");
    menu.addItem(3, "Cave");
    menu.addItem(4, "Auditorium");
}
