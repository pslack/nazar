//
//  MouseController.cpp
//  Nazar
//
//  Created by Peter J Slack on 2013-10-03.
//
//



#include "NazarProject.h"

#include "MouseEventSenderMAC.h"


void MouseController::moveMouse(int x, int y)
{
    
    nazarMouseMove(x, y);
    
}
void MouseController::rightClickMouse(int x, int y)
{
    
    nazarRightClick(x, y);
    
}
void MouseController::leftClickMouse(int x, int y)
{
    
    nazarLeftClick(x, y);
    
}
void MouseController::leftClickMouseControl(int x, int y)
{
    
    nazarLeftClickControl(x, y);
    
}
void MouseController::doubleClickMouse(int x, int y)
{
    
    nazarDoubleClick(x, y);
    
}

void MouseController::timerTick(int64 tick){
    previousTimeStamp = currentTimeStamp;
    currentTimeStamp = tick;
    queryMouse();
}




void MouseController::queryMouse(){
    Point<int> mp = mouseIn.getScreenPosition();
    
    
    if (mp == currentScreenPosition){
    }else{
        currentScreenPosition = mp;
        DBG("msmv detected:" + String(mp.getX()) + ":"+String(mp.getY()));
        
    }
    
    
    const MessageManagerLock mmLock;
    // the event loop will now be locked so it's safe to make a few calls..

        NazarApplication * app = (NazarApplication *)JUCEApplication::getInstance();
        app->postMouseLocation(mp.getX(), mp.getY(), currentTimeStamp);

    
    
    
}
