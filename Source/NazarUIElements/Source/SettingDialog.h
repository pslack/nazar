/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_594E0290E185954C__
#define __JUCE_HEADER_594E0290E185954C__

//[Headers]     -- You can add your own extra header files here --
#include "../../../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SettingDialog  : public DialogWindow,
                       public SliderListener,
                       public ButtonListener
{
public:
    //==============================================================================
    SettingDialog ();
    ~SettingDialog();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> latency;
    ScopedPointer<Label> label;
    ScopedPointer<Label> Camera0;
    ScopedPointer<Label> Camera1;
    ScopedPointer<ToggleButton> ViewCamera0;
    ScopedPointer<ToggleButton> ViewCamera1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingDialog)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_594E0290E185954C__
