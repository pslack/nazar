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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "NazarProject.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SettingDialog::SettingDialog () : DialogWindow("Nazar Settings",Colour::fromFloatRGBA(.4, .4, .4, 1.0),true,true)
{
    
    
    Component::addChildComponent (latency = new Slider ("Latency"));
    latency->setRange (60, 500, 1);
    latency->setSliderStyle (Slider::LinearHorizontal);
    latency->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    latency->addListener (this);

    latency->setVisible(true);
    
    Component::addChildComponent (label = new Label ("new label",
                                          "Latency Setting"));
 //   label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    label->setVisible(true);
    
    Component::addChildComponent (Camera0 = new Label ("new label",
                                            "Camera 0 : 0.00"));
    Camera0->setFont (Font (15.00f, Font::plain));
    Camera0->setJustificationType (Justification::centredLeft);
    Camera0->setEditable (false, false, false);
    Camera0->setColour (TextEditor::textColourId, Colours::black);
    Camera0->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    Camera0->setVisible(true);
    
    Component::addChildComponent (Camera1 = new Label ("new label",
                                            "Camera 1 : 0.00"));
    Camera1->setFont (Font (15.00f, Font::plain));
    Camera1->setJustificationType (Justification::centredLeft);
    Camera1->setEditable (false, false, false);
    Camera1->setColour (TextEditor::textColourId, Colours::black);
    Camera1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    Camera1->setVisible(true);
    
    Component::addChildComponent (ViewCamera0 = new ToggleButton ("new toggle button"));
    ViewCamera0->setButtonText ("View Camera 0");
    ViewCamera0->addListener (this);
    ViewCamera0->setVisible(true);
    
    Component::addChildComponent (ViewCamera1 = new ToggleButton ("new toggle button"));
    ViewCamera1->setButtonText ("View Camera 1");
    ViewCamera1->addListener (this);
    ViewCamera1->setVisible(true);
    

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    setResizable(false, false);
    //[/Constructor]
}

SettingDialog::~SettingDialog()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    latency = nullptr;
    label = nullptr;
    Camera0 = nullptr;
    Camera1 = nullptr;
    ViewCamera0 = nullptr;
    ViewCamera1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SettingDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

//    g.fillAll (Colours::white);

    g.setColour (Colour (0xff2a58a5));
    g.fillRect (20, 68, 340, 12);

    g.setColour (Colour (0xff5e554a));
    g.fillRect (20, 92, 340, 12);
    
    
    DBG("pnt");
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SettingDialog::resized()
{
    latency->setBounds (16, 32, 352, 32);
    label->setBounds (16, 16, 150, 24);
    Camera0->setBounds (368, 64, 150, 24);
    Camera1->setBounds (368, 88, 150, 24);
    ViewCamera0->setBounds (24, 120, 150, 24);
    ViewCamera1->setBounds (168, 120, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    repaint();
    //[/UserResized]
}

void SettingDialog::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == latency)
    {
        //[UserSliderCode_latency] -- add your slider handling code here..
        //[/UserSliderCode_latency]
    }

    //[UsersliderValueChanged_Post]
    
    //[/UsersliderValueChanged_Post]
}

void SettingDialog::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ViewCamera0)
    {
        //[UserButtonCode_ViewCamera0] -- add your button handler code here..
        //[/UserButtonCode_ViewCamera0]
    }
    else if (buttonThatWasClicked == ViewCamera1)
    {
        //[UserButtonCode_ViewCamera1] -- add your button handler code here..
        //[/UserButtonCode_ViewCamera1]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingDialog" componentName=""
                 parentClasses="public DialogWindow" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="20 68 340 12" fill="solid: ff2a58a5" hasStroke="0"/>
    <RECT pos="20 92 340 12" fill="solid: ff5e554a" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="Latency" id="8ecef6cdcf42378a" memberName="latency" virtualName=""
          explicitFocusOrder="0" pos="16 32 352 32" min="60" max="500"
          int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8fee519568642e75" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Latency Setting" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6f31fc951c471ca" memberName="Camera0" virtualName=""
         explicitFocusOrder="0" pos="368 64 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Camera 0 : 0.00" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8cccbf5c4fe976ad" memberName="Camera1" virtualName=""
         explicitFocusOrder="0" pos="368 88 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Camera 1 : 0.00" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="1f5926e90f7ad042" memberName="ViewCamera0"
                virtualName="" explicitFocusOrder="0" pos="24 120 150 24" buttonText="View Camera 0"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="da86f75e87ac6fd5" memberName="ViewCamera1"
                virtualName="" explicitFocusOrder="0" pos="168 120 150 24" buttonText="View Camera 1"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
