//
//  MouseEventSenderWIN.cpp
//  Nazar
//
//  Created by Peter J Slack on 2013-10-03.
//
//




/*
void PostMouseEvent(CGMouseButton button, CGEventType type, const CGPoint point)
{
    
    
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, type, point, button);
    CGEventSetType(theEvent, type);
    CGEventPost(kCGHIDEventTap, theEvent);
    CFRelease(theEvent);
}

void PostKeyboardEvent(CGKeyCode virtualKey,bool keyDown){
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    CGEventRef theEvent= CGEventCreateKeyboardEvent(source,virtualKey ,keyDown );
    CGEventPost(kCGHIDEventTap,theEvent);
    CFRelease(theEvent);
    CFRelease(source);
    
}
*/

void nazarLeftClick(int x, int y)
{
 
}

void nazarRightClick(int x, int y)
{

}

void nazarLeftClickControl(int x,int y){
  
    

}

void nazarDoubleClick(int x, int y){

   

}

void nazarMouseMove(int x, int y)
{
   
    
}