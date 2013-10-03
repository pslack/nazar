//
//  TargetTracker.cpp
//  Nazar
//
//  Created by Peter J Slack on 13-09-29.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#include "NazarProject.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <math.h>

using namespace cv;
using namespace std;
using namespace juce;

void TargetTracker::run(){


    std::vector<std::vector<cv::Point>> squares;
    
    cv::Mat frame_gray , thresh;
    
    cvtColor( inputValue, frame_gray, cv::COLOR_BGR2GRAY );
//    equalizeHist( frame_gray, frame_gray );
    
   cv::threshold(frame_gray, thresh, 190, 255, cv::THRESH_BINARY);
    
    cv::Mat bw;
    cv::Canny(thresh, bw, 0, 255, 5);
    
    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(bw.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // The array for storing the approximation curve
    std::vector<cv::Point> approx;

    // We'll put the labels in this destination image
    cv::Mat dst = inputValue.clone();
    
    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        cv::approxPolyDP(
                         cv::Mat(contours[i]), 
                         approx, 
                         cv::arcLength(cv::Mat(contours[i]), true) * 0.02, 
                         true
                         );
        
        // Skip small or non-convex objects 
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;
    
        if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();
            
            // Use the degrees obtained above and the number of vertices
            // to determine the shape of the contour
            if (vtc == 4 )
            {
                // Detect rectangle or square
                cv::Rect r = cv::boundingRect(contours[i]);
                double ratio = std::abs(1 - (double)r.width / r.height);
                squares.push_back(contours[i]);
             }        
        
        }
    
    }    
    
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const cv::Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(dst, &p, &n, 1, true, Scalar(0,255,0), 1, 4);
    }
    

    
    
    const MessageManagerLock mmLock;
    // the event loop will now be locked so it's safe to make a few calls..
  
if(frameBuffer)    
    imshow(cv::String(processName.getCharPointer()), dst);

    
    frame_gray.release();
    thresh.release();
    inputValue.release();
    
    int64 now = Time::getHighResolutionTicks();
    double totaltime = 1000.0 * Time::highResolutionTicksToSeconds (now - timeStamp);
    lastCalculatedLatency = totaltime;
//    DBG("Tracker latency(ms)"+ juce::String(processName)+ "->" + juce::String(totaltime));
    
    

}