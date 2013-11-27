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


cv::Point2f compute2DPolygonCentroid(const cv::Point* vertices, int vertexCount)
{
    cv::Point2f centroid = cv::Point2f(0, 0);
    double signedArea = 0.0;
    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area
    
    // For all vertices except last
    int i=0;
    for (i=0; i<vertexCount-1; ++i)
    {
        x0 = vertices[i].x;
        y0 = vertices[i].y;
        x1 = vertices[i+1].x;
        y1 = vertices[i+1].y;
        a = x0*y1 - x1*y0;
        signedArea += a;
        centroid.x += (x0 + x1)*a;
        centroid.y += (y0 + y1)*a;
    }
    
    // Do last vertex
    x0 = vertices[i].x;
    y0 = vertices[i].y;
    x1 = vertices[0].x;
    y1 = vertices[0].y;
    a = x0*y1 - x1*y0;
    signedArea += a;
    centroid.x += (x0 + x1)*a;
    centroid.y += (y0 + y1)*a;
    
    signedArea *= 0.5;
    centroid.x /= (6.0*signedArea);
    centroid.y /= (6.0*signedArea);
    
    return centroid;
}



void TargetTracker::run(){


    std::vector<std::vector<cv::Point>> squares;
    
    cv::Mat frame_gray , thresh;
    
    cvtColor( inputValue, frame_gray, cv::COLOR_BGR2GRAY );
//    equalizeHist( frame_gray, frame_gray );
    
    
    double maxVal = 0;
    cv::minMaxLoc(frame_gray, NULL, &maxVal, NULL, NULL);
    cv::Mat bw;
    
    
    cv::threshold(frame_gray, thresh, maxVal - 90, 255, cv::THRESH_BINARY);
    
    cv::Mat element= cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
    cv::erode(thresh, thresh, element);
    cv::dilate(thresh, thresh, element);

    
    
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
                squares.push_back(approx);
             }        
        
        }
    
    }    
    
    float x_bar=0;
    float y_bar=0;
    bool trackerfound = false;
    
    if(squares.size() == 2){
        for( size_t i = 0; i < squares.size(); i++ )
        {
            const cv::Point* p = &squares[i][0];
            int n = (int)squares[i].size();
            polylines(dst, &p, &n, 1, true, Scalar(0,255,0), 1, 4);
            cv::Point q=compute2DPolygonCentroid(p, n);
            x_bar += q.x;
            y_bar += q.y;
            
        }
        
        x_bar = x_bar / 2;
        y_bar = y_bar / 2;
        trackerfound = true;
        
    }

    
    
    const MessageManagerLock mmLock;
    // the event loop will now be locked so it's safe to make a few calls..
    if(trackerfound){
      NazarApplication * app = (NazarApplication *)JUCEApplication::getInstance();
        app->postTargetTrackerPoint(x_bar, y_bar, timeStamp);
    }
    
    
if(frameBuffer)    
    imshow(cv::String(processName.getCharPointer()), dst);

    
    frame_gray.release();
    thresh.release();
    inputValue.release();
    
    juce::int64 now = Time::getHighResolutionTicks();
    double totaltime = 1000.0 * Time::highResolutionTicksToSeconds (now - timeStamp);
    lastCalculatedLatency = totaltime;
//    DBG("Tracker latency(ms)"+ juce::String(processName)+ "->" + juce::String(totaltime));
    
    

}