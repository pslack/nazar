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
#include <cv.h>
#include <highgui.h>

void EyeTracker::run(){
    
    
    
    cv::Mat frame_gray , thresh;
    
    cvtColor( inputValue, frame_gray, cv::COLOR_BGR2GRAY );
    //    equalizeHist( frame_gray, frame_gray );
    
//    double minVal;
//    cv::minMaxLoc(frame_gray, &minVal);
//    
//    
//
//    
    // Quantize the hue to 256 levels
//    int histSize=256;
//    // saturation varies from 0 (black-gray-white) to
//    float hranges[] = { 0, 256 };
//    const float* ranges[] = { hranges };
//    cv::Mat hist;
//    
//    cv::calcHist( &frame_gray, 1, 0, cv::Mat(), // do not use mask
//             hist, 1, &histSize, ranges,
//             true, // the histogram is uniform
//             false );
//    double maxVal=0;
//    minMaxLoc(hist, 0, &maxVal, 0, 0);
//    
//    // Draw the histograms for R, G and B
//    int hist_w = 256; int hist_h = 400;
//    int bin_w = cvRound( (double) hist_w/histSize );
//    
//    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );
//    /// Normalize the result to [ 0, histImage.rows ]
//    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
//    
//    float lowestSpike = MAXFLOAT;
//    
//    //calculate colours in histogram > 40 pixels
//    for(int i=1; i< histSize;i++){
//        float tval = hist.at<float>(i);
//        if(tval > 40){
//            if (tval < lowestSpike) {
//                lowestSpike = tval;
//            }
//        }
//    }
//    
//    /// Draw for each channel
//    for( int i = 1; i < histSize; i++ )
//    {
//        line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
//             cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
//             cv::Scalar( 255, 0, 0), 2, 8, 0  );
//    }
//
//
//    cv::inRange(frame_gray, 0, lowestSpike + 40, thresh);
//
//    cv::Mat kern = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size2d(7,7));
//    cv::dilate(thresh, thresh, kern);
//    cv::Mat spec_image;
//    cv::inRange(frame_gray, 0, 250, spec_image);
//    cv::erode(spec_image, spec_image, kern);
//    
//    cv::Mat edges;
//    cv::Canny(frame_gray, edges, lowestSpike, 5);
//    
//    cv::min(edges, spec_image, edges);
//    cv::min(edges, thresh, edges);
    
    
//    cv::threshold(frame_gray, thresh, 200, 255, cv::THRESH_BINARY);
    

    double minVal = 0;
    cv::minMaxLoc(frame_gray, &minVal, NULL, NULL, NULL);
    cv::Mat bw;
   
    threshold(frame_gray, thresh, minVal + 10, 255, cv::THRESH_BINARY_INV);
    
//    cv::Mat kern = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size2d(7,7));
//    cv::dilate(thresh, thresh, kern);
//    cv::Mat spec_image;
//    cv::inRange(frame_gray, 0, 250, spec_image);
//    cv::erode(spec_image, spec_image, kern);

    
    
//    cv::Canny(thresh, bw, 0, 255, 5);

    //(Optional) remove noise (small areas of white pixels)
    
    cv::Mat element= cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3), cv::Point(1, 1));
    cv::erode(thresh, thresh, element);
    cv::dilate(thresh, thresh, element);
     
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point2i> > contours;
    cv::findContours(thresh, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    
    //find contour with max area
    int maxArea = 0;
    cv::Rect maxContourRect;
    for (int i=0; i<contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cv::Rect rect = boundingRect(contours[i]);
        double squareKoef = ((double) rect.width)/rect.height;
        
        //check if contour is like square (shape)
#define SQUARE_KOEF 1.5
        if (area>maxArea && squareKoef < SQUARE_KOEF && squareKoef > 1.0/SQUARE_KOEF)
        {
            maxArea = area;
            maxContourRect = rect;
        }
    }
    
    if (maxArea != 0)
    {
        cv::Rect drawRect = cv::Rect(maxContourRect.x-maxContourRect.width,
                                     maxContourRect.y-maxContourRect.height, maxContourRect.width*3, maxContourRect.height*3);
        
        cv::rectangle(inputValue, drawRect, cv::Scalar(0,255,0), 1);
        
    }
    
    
    
//    // Find contours
//    std::vector<std::vector<cv::Point> > contours;
//    cv::findContours(bw.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//    
//    // The array for storing the approximation curve
//    std::vector<cv::Point> approx;
//    
//    // We'll put the labels in this destination image
//    cv::Mat dst = inputValue.clone();
//    std::vector<std::vector<cv::Point>> squares;
//
//    for (int i = 0; i < contours.size(); i++)
//    {
//        // Approximate contour with accuracy proportional
//        // to the contour perimeter
//        cv::approxPolyDP(
//                         cv::Mat(contours[i]),
//                         approx,
//                         cv::arcLength(cv::Mat(contours[i]), true) * 0.02,
//                         true
//                         );
//        
//        // Skip small or non-convex objects
//        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
//            continue;
//        
//        if (approx.size() > 6)
//        {
//            // Number of vertices of polygonal curve
//            int vtc = approx.size();
//            
//            // Use the degrees obtained above and the number of vertices
//            // to determine the shape of the contour
//            if (vtc > 6 )
//            {
//                // Detect rectangle or square
//                cv::Rect r = cv::boundingRect(contours[i]);
//                double ratio = std::abs(1 - (double)r.width / r.height);
//                squares.push_back(contours[i]);
//            }
//            
//        }
//        
//    }
//    
//    for( size_t i = 0; i < squares.size(); i++ )
//    {
//        const cv::Point* p = &squares[i][0];
//        int n = (int)squares[i].size();
//        polylines(dst, &p, &n, 1, true, cv::Scalar(0,255,0), 1, 4);
//    }
    

    
    
    
    
    
    if(!frameBuffer){
    
        const MessageManagerLock mmLock;
        // the event loop will now be locked so it's safe to make a few calls..
        
        cv::namedWindow( "Source", 1 );
//        cv::imshow( "Source", spec_image );
//
        cv::namedWindow( "H-S Histogram", 1 );
//        cv::imshow( "H-S Histogram", bw);

        cv::namedWindow( "xxx", 1 );
        cv::imshow( "xxx", inputValue);
        
        
    }
    
    
    
//    cv::calcHist(frame_gray, 1, i[0],mask , hist, 256, 256, <#const float **ranges#>)
    // apply Canny. Take the upper threshold from slider
    // and set the lower to 0 (which forces edges merging)
    //   Canny(thresh, gray0, 0, 50, 5);
    


    
    frame_gray.release();
    thresh.release();
    inputValue.release();

    int64 now = Time::getHighResolutionTicks();
    double totaltime = 1000.0 * Time::highResolutionTicksToSeconds (now - timeStamp);
    
    lastCalculatedLatency = totaltime;
    
    //DBG("Tracker latency(ms)"+ juce::String(processName)+ "->" + juce::String(totaltime));
    
    
}