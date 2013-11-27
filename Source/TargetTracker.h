#ifndef TARGETTRACKER_H_INCLUDED
#define TARGETTRACKER_H_INCLUDED

class TargetTracker : public ProcessLoop<cv::Mat,cv::Mat> {
public:
    TargetTracker(juce::String myName ,bool myFrame) : ProcessLoop<cv::Mat, cv::Mat>(myName, myFrame){}
    ~TargetTracker(){}
    void run();
};

#endif

