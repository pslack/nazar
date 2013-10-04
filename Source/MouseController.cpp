//
//  MouseController.cpp
//  Nazar
//
//  Created by Haig's Tower on 2013-10-03.
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




void MouseController::queryMouse(){
    Point<int> mp = mouseIn.getScreenPosition();
    if (mp == currentScreenPosition){
    }else{
        currentScreenPosition = mp;
        DBG("msmv detected:" + String(mp.getX()) + ":"+String(mp.getY()));
        
    }
    
    
}
