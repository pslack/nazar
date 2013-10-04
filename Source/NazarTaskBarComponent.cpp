//
//  NazarTaskBarComponent.cpp
//  Nazar
//
//  Created by Peter J Slack on 2013-10-04.
//
//

#include "NazarProject.h"
NazarTaskbarComponent::NazarTaskbarComponent()
{
    setIconImage (createImageForIcon());
    setIconTooltip ("Juce Demo App!");
}

Image NazarTaskbarComponent::createImageForIcon()
{
    Image icon (Image::RGB, 32, 32, true);
    
    Graphics g (icon);
    
    // This draws an icon which is just a square with a "j" in it..
    g.fillAll (Colours::lightblue);
    g.setColour (Colours::black);
    g.setFont (Font ((float) icon.getHeight(), Font::bold));
    g.drawText ("j", 0, 0, icon.getWidth(), icon.getHeight(), Justification::centred, false);
    
    return icon;
}

void NazarTaskbarComponent::mouseDown (const MouseEvent&)
{
    // On OSX, there can be problems launching a menu when we're not the foreground
    // process, so just in case, we'll first make our process active, and then use a
    // timer to wait a moment before opening our menu, which gives the OS some time to
    // get its act together and bring our windows to the front.
    
    Process::makeForegroundProcess();
    startTimer (50);
}

void NazarTaskbarComponent::timerCallback()
{
    stopTimer();
    
    PopupMenu m;
    m.addItem(1,"Goodbye");
    m.addItem(2,"Settings");
    m.addItem(3,"Calibrate");
    
    // It's always better to open menus asynchronously when possible.
    m.showMenuAsync (PopupMenu::Options(),
                     ModalCallbackFunction::forComponent (menuInvocationCallback, this));
}

// This is invoked when the menu is clicked or dismissed
void NazarTaskbarComponent::menuInvocationCallback (int chosenItemID, NazarTaskbarComponent*)
{
    NazarApplication * app = (NazarApplication *)JUCEApplication::getInstance();
    
    switch (chosenItemID) {
        case 1:
            app->systemRequestedQuit();
            break;
        case 2:
            app->invokeDirectly(CommandIDs::doCalibration, true);
        case 3:
            app->beginLearnMode();
            break;
        default:
            break;
    };
    
    
}
