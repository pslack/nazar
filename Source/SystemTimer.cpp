//
//  SystemTimer.cpp
//  Nazar
//
//  Created by Peter J Slack on 13-09-25.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#include "NazarProject.h"

void SystemTimer::timerCallback (int timerID){

    currentTimeStamp = Time::getHighResolutionTicks() - baseTime;
    //the system monitor tuimer looks after things like shutdown etc
    if(timerID == SYSTEM_MONITOR_TIMER_ID){
        if(iShouldShutTheApplication){
            shutTheSystemDown();
        }
        //DBG("System pluse");
    }else{
    
    // This iterates the map, printing all of its key -> value pairs..
    for (HashMap<TimerListener *, int>::Iterator i (systemTimerGroup); i.next();)
        if(i.getValue() == timerID){
            i.getKey()->timerTick(currentTimeStamp);
        }
        
    }
}



void SystemTimer::shutTheSystemDown(){
    
    if (systemTimerGroup.size() == 0) {
        
        
        JUCEApplication::getInstance()->quit();
 
    }
    //shut off non essential timers
    
    
    stopTimer(LATENCY_TIMER_ID);
    
    //tell all the listeners to shut down
    
    // This iterates the map, printing all of its key -> value pairs..
    for (HashMap<TimerListener *, int>::Iterator i (systemTimerGroup); i.next();){
        i.getKey()->shutDownRequested();
        i.getKey()->timerTick(0);
    
    }
    
    
}

void SystemTimer::startShutDownTimerSequence(){
    iShouldShutTheApplication = true;

}



SystemTimer::SystemTimer() : MultiTimer( ){
   baseTime = Time::getHighResolutionTicks();
   iShouldShutTheApplication = false;
   latency = DEFAULT_LATENCY_MS;

    startTimer(SYSTEM_MONITOR_TIMER_ID, 1500);
}

void SystemTimer::startTimers(){
    //startTimer(SYSTEM_MONITOR_TIMER_ID, 1500);
    startTimer(LATENCY_TIMER_ID, latency);
}
void SystemTimer::stopTimers(){
    
    //stopTimer(SYSTEM_MONITOR_TIMER_ID);
    stopTimer(LATENCY_TIMER_ID);
}

SystemTimer::~SystemTimer(){
    stopTimer(SYSTEM_MONITOR_TIMER_ID);
    stopTimer(LATENCY_TIMER_ID);
    // This iterates the map, printing all of its key -> value pairs..

    for (HashMap<TimerListener *, int>::Iterator i (systemListeners); i.next();){
        delete i.getKey();
    }

    
    
}


void SystemTimer::registerListener(int ID , TimerListener * listener){

    systemTimerGroup.set(listener, ID);
    systemListeners.set(listener, ID);
}

void SystemTimer::removeListener(TimerListener * listener){
    systemTimerGroup.remove(listener);
}


void SystemTimer::setTransportState(bool isPlaying){

    transportState = isPlaying;
    
    if(transportState){
        startTimers();
    }else{
        stopTimers();
    }
}

void SystemTimer::setLatency(int latencyValue){
    
    latency = latencyValue;
    stopTimer(LATENCY_TIMER_ID);
    startTimer(LATENCY_TIMER_ID, latency);
    
}

int SystemTimer::getLatency(){
    return(latency);
}
