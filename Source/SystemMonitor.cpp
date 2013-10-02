/*
  ==============================================================================

    SystemMonitor.cpp
    Created: 21 Sep 2013 12:27:15pm
    Author:  Peter Slack

  ==============================================================================
*/

#include "SystemMonitor.h"

using namespace cv;
using namespace juce;

SystemMonitor::SystemMonitor (juce::String myName,int camera_id ) : Thread(myName) {
    iShouldExit = false;
    cameraID = camera_id;
    windowName=cv::String(myName.getCharPointer());
    DBG(/*juce::String((int64)getCurrentThreadId()) + */ ": System Monitor started");


}

SystemMonitor::~SystemMonitor(){
    DBG(/*juce::String((int64)getCurrentThreadId()) +*/ ": entered to remove SysMon");   
//    jassert(Thread::getCurrentThread()->getThreadId() != getThreadId())
    //we can't shut down our own thread
    jassert (getCurrentThreadId() != getThreadId()); 
    if (isThreadRunning())
    {
        signalThreadShouldExit();
        notify();
        
            waitForThreadToExit (500);
    }
}

void SystemMonitor::shouldExit(){
    DBG(/*juce::String((int64)getCurrentThreadId()) +*/ ": System Monitor told to shut");
    
    iShouldExit=true;
}

/** Global variables */
cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
cv::String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
cv::String window_name = "Capture - Face detection";


void SystemMonitor::run(){
//    cv::VideoCapture capture;
//    DBG(String(cv::getBuildInformation()));
//    while (true) {
//        if(iShouldExit)
//            break;
//        
//        findCamera();
//        try{
//            sleep(1000);
//        }
//        catch(std::exception c ){
//            DBG("Interrupted");
//            break;
//        }
//    }
//    
//

    cv::VideoCapture capture;
    cv::Mat frame;
    
    char wdBuffer[2048];
    juce::File appPath=juce::File::getSpecialLocation(File::SpecialLocationType::hostApplicationPath);
    DBG(appPath.getFullPathName());
    if(getwd(wdBuffer) != NULL)
        DBG ("homedir ->" + juce::String(wdBuffer));
    
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    { DBG("--(!)Error loading face cascade\n"); 
        return; 
    }
    if( !eyes_cascade.load( eyes_cascade_name ) )
    { 
        DBG("--(!)Error loading eyes cascade\n"); 
        return ; 
    }
    
    //-- 2. Read the video stream
    capture.open( cameraID );
    if ( ! capture.isOpened() ) { DBG("--(!)Error opening video capture\n"); return; }
    
    while (!iShouldExit  )
    {
        capture.read(frame);
        
        if( frame.empty() )
        {
            //DBG(" --(!) No captured frame -- Break!");
            //            break;
            sleep(50);
        }else{
        
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        }
            
    }
    
    DBG(  ": Sys Monitor Ended Normally");
    capture.release();
    
    cv::destroyWindow(windowName);
    
    return;

    
    
}

/** @function detectAndDisplay */
void SystemMonitor::detectAndDisplay( cv::Mat frame )
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    
    cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
        
        cv::Mat faceROI = frame_gray( faces[i] );
        std::vector<cv::Rect> eyes;
        
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
        
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
   imshow( windowName, frame );
    
}


int SystemMonitor::findCamera() { 
    return 0; 
}