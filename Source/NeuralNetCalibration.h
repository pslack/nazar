#ifndef NEURALNETCALIBRATION_H_INCLUDED
#define NEURALNETCALIBRATION_H_INCLUDED

class NeuralNetCalibration : public Thread, public TimerListener {
public:
    NeuralNetCalibration(juce::String myName,SystemTimer * sysTime);
    ~NeuralNetCalibration();
    void process();
    cv::Point2f predict(float eye_x,float eye_y,float tracker_x, float tracker_y);
    void shutDownRequested(){iShouldExit=true;}
    void train();
    void setTrained(bool trained){
        isTrained=trained;
    }
    bool isBrainTrained(){return isTrained;}
protected:
    void run();
    void timerTick(juce::int64 ID);
    CvANN_MLP machineBrain;
    juce::int64 previousTick;
    juce::int64 currentTick;
    float eye_x,eye_y,target_x,target_y;
    bool isTrained;
    WaitableEvent timerWait;
    bool iShouldExit;
    SystemTimer * mySystemTimer;

};

#endif