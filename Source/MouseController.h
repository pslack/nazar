//
//  MouseController.h
//  Nazar
//
//  Created by Peter J Slack on 2013-10-03.
//
//

#ifndef MOUSECONTROLLER_H_INCLUDED
#define MOUSECONTROLLER_H_INCLUDED

class NazarMouseEvent{
public:
    juce::int64 timeStamp;
    int nazarEventID;
};

class MouseController : public Thread, public TimerListener{
    
public:
    MouseController();
    
    void run(){
        
    }
    void moveMouse(int x, int y);
    void rightClickMouse(int x, int y);
    void leftClickMouse(int x, int y);
    void doubleClickMouse(int x, int y);
    void leftClickMouseControl(int x, int y);
    void timerTick(juce::int64 tick);
    void shutDownRequested(){
    }
    
    ~MouseController(){}
    int to(int x,int y);
    
private:
    juce::int64 currentTimeStamp;
    juce::int64 previousTimeStamp;
    
    void queryMouse();
    juce::MouseInputSource mouseIn;
    juce::Point<int> currentScreenPosition;
    int mouseTimerCount;
    
private:
    std::vector<NazarMouseEvent> mouseQueue;
    
};




#endif /* defined(__Nazar__MouseController__) */
