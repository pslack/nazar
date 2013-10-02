/*
  ==============================================================================

    SystemMonitor.h
    Created: 21 Sep 2013 12:27:14pm
    Author:  Peter Slack

  ==============================================================================
*/

#ifndef SYSTEMMONITOR_H_INCLUDED
#define SYSTEMMONITOR_H_INCLUDED

#include "NazarProject.h"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class SystemMonitor : public Thread
{
public:
    SystemMonitor(juce::String name,int camera_ID);
    ~SystemMonitor();
    void run();
    int findCamera();
    void detectAndDisplay( cv::Mat frame );
    void shouldExit();
protected:
    int cameraID=0;
    bool iShouldExit=false;
    cv::String windowName;
private:
    
};



#endif  // SYSTEMMONITOR_H_INCLUDED
