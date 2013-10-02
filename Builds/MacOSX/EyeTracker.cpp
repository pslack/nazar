//
//  EyeTracker.cpp
//  Nazar
//
//  Created by Doug Mummenhoff on 13-09-30.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

//
//  TargetTracker.cpp
//  Nazar
//
//  Created by Peter J Slack on 13-09-29.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#include "NazarProject.h"

void EyeTracker::run(){
    
    
    
    cv::Mat frame_gray , thresh;
    
    cvtColor( inputValue, frame_gray, cv::COLOR_BGR2GRAY );
    //    equalizeHist( frame_gray, frame_gray );
    
    cv::threshold(frame_gray, thresh, 60, 255, cv::THRESH_BINARY);
    
    // apply Canny. Take the upper threshold from slider
    // and set the lower to 0 (which forces edges merging)
    //   Canny(thresh, gray0, 0, 50, 5);
    
// if(!frameBuffer)   
// imshow(cv::String(processName.getCharPointer()), thresh);
    
    frame_gray.release();
    thresh.release();
    inputValue.release();

    int64 now = Time::getHighResolutionTicks();
    double totaltime = 1000.0 * Time::highResolutionTicksToSeconds (now - timeStamp);
    
    DBG("Tracker latency(ms)"+ juce::String(processName)+ "->" + juce::String(totaltime));
    
    
}