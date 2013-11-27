#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include "opencv/ml.h"
#include "opencv2/highgui/highgui.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "../JuceLibraryCode/JuceHeader.h"





 


#define MAX_TRAINING_POINTS 1500



enum NAZAR_EVENTID{
    NAZAR_MOUSE_MOVE = 0x0000,
    NAZAR_MOUSE_RIGHT_CLICK = 0x0001,
    NAZAR_MOUSE_LEFT_CLICK = 0x0002,
    NAZAR_MOUSE_DOUBLE_CLICK = 0x0003
    
    
};

#include "Commands.h"

//Messages

const String MESSAGE_TIMER_TICK ="msg_tmt";

const int DEFAULT_LATENCY_MS = 100;

//Timer IDs
const int SYSTEM_MONITOR_TIMER_ID = 0;
const int LATENCY_TIMER_ID =1;

//Globals
#include "NazarUIElements/Source/SettingDialog.h"

#include "TimerListener.h"
#include "SystemTimer.h"
#include "ProcessLoop.h"

#include "CameraInput.h"
#include "EyeTracker.h"
#include "MouseController.h"
#ifdef JUCE_MAC

  #include "MouseEventSenderMAC.h"

#else

  #include "MouseEventSenderWIN.h"

#endif

#include "NeuralNetCalibration.h"
#include "NazarUIElements/Source/SettingDialog.h"
#include "TargetTracker.h"




//==============================================================================
#if JUCE_WINDOWS || JUCE_LINUX || JUCE_MAC

// Just add a simple icon to the Window system tray area..
class NazarTaskbarComponent  : public SystemTrayIconComponent,
private Timer
{
public:
    NazarTaskbarComponent();
    
    Image createImageForIcon();
    void mouseDown (const MouseEvent&);
    void timerCallback();
    static void menuInvocationCallback (int chosenItemID, NazarTaskbarComponent*);
};

#endif




#endif