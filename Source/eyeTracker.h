#ifndef EYETRACKER_H_INCLUDED
#define EYETRACKER_H_INCLUDED


class EyeTracker : public ProcessLoop<cv::Mat,cv::Mat> {
public:
    EyeTracker(juce::String myName, bool myFrame) : ProcessLoop<cv::Mat, cv::Mat>(myName ,myFrame){}
    ~EyeTracker(){}
    void run();
};

#endif