#ifndef SYSTEMTIMER_H_INCLUDED
#define SYSTEMTIMER_H_INCLUDED


class SystemTimer : public MultiTimer 
{   
public:
    
    
    SystemTimer();
    ~SystemTimer();
    void timerCallback (int timerID);
    
    void setLatency(int latency);
    int getLatency();
    void registerListener(int ID , TimerListener * listener);
    void removeListener(TimerListener * listener);
    void startShutDownTimerSequence();
    double startTimeStamp;
    void startTimers();
    void stopTimers();
    void setTransportState(bool isPlaying);
    
protected:
    juce::int64 currentTimeStamp;
    HashMap<TimerListener *,int> systemListeners;
    HashMap<TimerListener *,int> systemTimerGroup;
    bool iShouldShutTheApplication;
    juce::int64 baseTime; // the timestamp when we booted the timer up
    //used as a relative base for our heartbeat


private:
    void shutTheSystemDown();
    int latency;
    bool transportState;
};

#endif
