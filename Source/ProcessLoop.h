#ifndef PROCESSLOOP_H_INCLUDED
#define PROCESSLOOP_H_INCLUDED

//T is input type , V is Type
template < class T, class V>

class ProcessLoop : public Thread{
    
public:
    ProcessLoop(juce::String myName, bool myFrameBuffer) : Thread(myName){
        processName=myName;
        frameBuffer = myFrameBuffer;
    }
    virtual void run() = 0;
    void process(T input_value, juce::int64 ts){
        timeStamp=ts;
        inputValue = input_value;
        startThread();
    }
    ~ProcessLoop(){lastCalculatedLatency=0.0;}
    
    juce::int64 timeStamp;
    T inputValue;
    juce::String processName;
    bool frameBuffer;
    double lastCalculatedLatency;
protected:
    
};



#endif