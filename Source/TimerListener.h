#ifndef TIMERLISTENER_H_INCLUDED
#define TIMERLISTENER_H_INCLUDED
//==============================================================================
/**
 Receives timer ticks
 
 Used by various classes, e.g. buttons when they are pressed, to tell listeners
 about something that's happened.
 
 */
class TimerListener
{
public:
    
    TimerListener(){}
    virtual ~TimerListener() {lastCalculatedLatency=0.0;}
    /** Overridden by your subclass to receive the timer tick.
     
     by a call to 
     */
    virtual void timerTick(juce::int64 ID) = 0;
    virtual void shutDownRequested() = 0;
    double lastCalculatedLatency;
     
};

#endif
