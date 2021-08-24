/*
  ==============================================================================

    PresetMenu.cpp
    Created: 22 Aug 2021 1:47:06am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void Pastel_VerbAudioProcessorEditor::setPresetMenuProps(juce::ComboBox &menu)
{
    /**Init all menus in hierarchical order backwards to be sure each is ready*/
    // Now init small menu
    setSmallMenuProps(smallMenu);
    
    // Now init medium menu
    setMediumMenuProps(mediumMenu);
    
    // Now init large menu
    setLargeMenuProps(largeMenu);
    
    // Now init space menu
    setSpaceMenuProps(spacesMenu);
    
    // Now init root menu
    addAndMakeVisible(menu);
    menu.setText("Presets");
    menu.getRootMenu()->addSubMenu("Space", spacesMenu);
    
    
    

}
