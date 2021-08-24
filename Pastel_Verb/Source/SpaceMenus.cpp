/*
  ==============================================================================

    SpaceMenus.cpp
    Created: 22 Aug 2021 7:46:38pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setSpaceMenuProps(juce::PopupMenu &menu)
{
    menu.addSubMenu("Small", smallMenu);
    menu.addSubMenu("Medium", mediumMenu);
    menu.addSubMenu("Large", largeMenu);
}
