//
//  MouseEventSenderMAC.cpp
//  Nazar
//
//  Created by Peter J Slack on 2013-10-03.
//
//


#include <ApplicationServices/ApplicationServices.h>
//



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


void nazarLeftClick(int x, int y)
{
    CGPoint point = CGPointMake(x, y);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventMouseMoved, point);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventLeftMouseDown, point);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventLeftMouseUp, point);
}

void nazarRightClick(int x, int y)
{
    CGPoint point = CGPointMake(x, y);
    PostMouseEvent(kCGMouseButtonRight, kCGEventMouseMoved, point);
    PostMouseEvent(kCGMouseButtonRight, kCGEventRightMouseDown, point);
    PostMouseEvent(kCGMouseButtonRight, kCGEventRightMouseUp, point);
}

void nazarLeftClickControl(int x,int y){
    CGPoint point = CGPointMake(x, y);
    PostKeyboardEvent((CGKeyCode)59, true);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventMouseMoved, point);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventLeftMouseDown, point);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventLeftMouseUp, point);
    PostKeyboardEvent((CGKeyCode)59, true);
    

}

void nazarDoubleClick(int x, int y){

    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, theEvent);
    CGEventSetType(theEvent, kCGEventLeftMouseUp);
    CGEventPost(kCGHIDEventTap, theEvent);
    
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 2);
    
    CGEventSetType(theEvent, kCGEventLeftMouseDown);
    CGEventPost(kCGHIDEventTap, theEvent);
    
    CGEventSetType(theEvent, kCGEventLeftMouseUp);
    CGEventPost(kCGHIDEventTap, theEvent);
    
    CFRelease(theEvent);

}

void nazarMouseMove(int x, int y)
{
    //    CGPoint newloc;
    //    CGEventRef eventRef;
    //    newloc.x = x;
    //    newloc.y = y;
    //
    //    eventRef = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, newloc,
    //                                       kCGMouseButtonCenter);
    //    //Apparently, a bug in xcode requires this next line
    //    CGEventSetType(eventRef, kCGEventMouseMoved);
    //    CGEventPost(kCGSessionEventTap, eventRef);
    //    CFRelease(eventRef);
    
    CGPoint point = CGPointMake(x, y);
    PostMouseEvent(kCGMouseButtonLeft, kCGEventMouseMoved, point);
    
    
    
}