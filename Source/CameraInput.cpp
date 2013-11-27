//
//  CameraInput.cpp
//  Nazar
//
//  Created by Peter J Slack on 13-09-25.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#include "NazarProject.h"

//using namespace juce;


CameraInput::CameraInput (juce::String myName,int camera_id ,SystemTimer * sysTime) : Thread(myName) {
    iShouldExit = false;
	 errorCount = 0 ;
	 mySystemTimer=NULL;
     cameraID = camera_id;
	 doubleBufferBit=false;
	 initialized = false;

    windowName=cv::String(myName.getCharPointer());
    DBG("Camera started : " + myName);
    mySystemTimer = sysTime;
    if(mySystemTimer != NULL)
        mySystemTimer->registerListener(LATENCY_TIMER_ID, (TimerListener *) this);

    //the camera likes to be opened on the display thread .. 
    capture.open( cameraID );
    
    startThread();
    
}


void CameraInput::shutDownRequested(){
    shouldExit();
}

void CameraInput::timerTick(juce::int64 ID){

    //has to come from thread main!!
    jassert (getCurrentThreadId() != getThreadId());
    currentTimeStamp=ID;
    cameraShutter.signal();
    
    
}

CameraInput::~CameraInput(){
}

void CameraInput::shouldExit(){
    DBG("Camera asked to exit : ");
    
    iShouldExit=true;
}

void CameraInput::run(){
    
    if ( ! capture.isOpened() ) { DBG("--(!)Error opening video capture\n"); return; }
    loadCameraProperties();
    
    juce::int64 now;
    double totaltime;
    
    while(!iShouldExit){
        cameraShutter.wait();
        
        //record the time when we took this snap
 //       currentTimeStamp = Time::getHighResolutionTicks();
        
        if(iShouldExit)
            break;

        if(errorCount > 60)
            iShouldExit = true;
        
        
        bool noframe = false;
        
        if(doubleBufferBit){
            capture.read(frame_1);
            if( frame_1.empty() )
            {
                DBG(" --(!) No captured frame -- Break!");
                errorCount++;
                noframe = true;
            } else {
                errorCount=0;
            }
        }
        else{
            capture.read(frame_0);
            if( frame_0.empty() )
            {
                noframe = true;
                DBG(" --(!) No captured frame -- Break!");
                errorCount++;
            }else{
                errorCount=0;
            }
        }
        
        //do the processing
        if(!noframe)
            processLoop();
        
        //flip the buffer bit
        doubleBufferBit = ! doubleBufferBit;
        

     
        //DBG("Camera latency(ms)"+ juce::String(cameraID)+ "->" + juce::String(totaltime));
    }
    
    
    capture.release();
    
    DBG("destroying camera processes: ");
    for (HashMap<ProcessLoop<cv::Mat, cv::Mat> *, bool>::Iterator i (process); i.next();){
        delete i.getKey();
    }
    process.clear();

    
    DBG("Camera Exit");
    if(mySystemTimer != NULL)
        mySystemTimer->removeListener( (TimerListener *) this);

}


void CameraInput::loadCameraProperties(){
/*
    CV_CAP_PROP_POS_MSEC Current position of the video file in milliseconds or video capture timestamp.
    CV_CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
    CV_CAP_PROP_POS_AVI_RATIO Relative position of the video file: 0 - start of the film, 1 - end of the film.
    CV_CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
    CV_CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
    CV_CAP_PROP_FPS Frame rate.
    CV_CAP_PROP_FOURCC 4-character code of codec.
    CV_CAP_PROP_FRAME_COUNT Number of frames in the video file.
    CV_CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
    CV_CAP_PROP_MODE Backend-specific value indicating the current capture mode.
    CV_CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
    CV_CAP_PROP_CONTRAST Contrast of the image (only for cameras).
    CV_CAP_PROP_SATURATION Saturation of the image (only for cameras).
    CV_CAP_PROP_HUE Hue of the image (only for cameras).
    CV_CAP_PROP_GAIN Gain of the image (only for cameras).
    CV_CAP_PROP_EXPOSURE Exposure (only for cameras).
    CV_CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
    CV_CAP_PROP_WHITE_BALANCE Currently not supported
    CV_CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)
*/
    
    if(capture.isOpened()){
        cameraSettings.setValue("CV_CAP_PROP_POS_MSEC",     capture.get(cv::CAP_PROP_POS_MSEC));
        cameraSettings.setValue("CV_CAP_PROP_POS_FRAMES",   capture.get(cv::CAP_PROP_POS_FRAMES));
        cameraSettings.setValue("CV_CAP_PROP_POS_AVI_RATIO",capture.get(cv::CAP_PROP_POS_AVI_RATIO));
        cameraSettings.setValue("CV_CAP_PROP_FRAME_WIDTH",  capture.get(cv::CAP_PROP_FRAME_WIDTH));
        cameraSettings.setValue("CV_CAP_PROP_FRAME_HEIGHT", capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        cameraSettings.setValue("CV_CAP_PROP_FPS",          capture.get(cv::CAP_PROP_FPS));
        cameraSettings.setValue("CV_CAP_PROP_FOURCC",       capture.get(cv::CAP_PROP_FOURCC));
        cameraSettings.setValue("CV_CAP_PROP_FRAME_COUNT",  capture.get(cv::CAP_PROP_FRAME_COUNT));
        cameraSettings.setValue("CV_CAP_PROP_FORMAT",       capture.get(cv::CAP_PROP_FORMAT));
        cameraSettings.setValue("CV_CAP_PROP_MODE",         capture.get(cv::CAP_PROP_MODE));
        cameraSettings.setValue("CV_CAP_PROP_BRIGHTNESS",   capture.get(cv::CAP_PROP_BRIGHTNESS));
        cameraSettings.setValue("CV_CAP_PROP_CONTRAST",     capture.get(cv::CAP_PROP_CONTRAST));
        cameraSettings.setValue("CV_CAP_PROP_SATURATION",   capture.get(cv::CAP_PROP_SATURATION));
        cameraSettings.setValue("CV_CAP_PROP_HUE",          capture.get(cv::CAP_PROP_HUE));
        cameraSettings.setValue("CV_CAP_PROP_GAIN",         capture.get(cv::CAP_PROP_GAIN));
        cameraSettings.setValue("CV_CAP_PROP_CONVERT_RGB",  capture.get(cv::CAP_PROP_CONVERT_RGB));
        cameraSettings.setValue("CV_CAP_PROP_EXPOSURE",     capture.get(cv::CAP_PROP_EXPOSURE));
 
    }
    
    StringPairArray  st = cameraSettings.getAllProperties();
    StringArray qt = st.getAllKeys();
    
    for(int i=0;i<qt.size();i++){
        
        DBG( qt[i]+ "->" + juce::String(cameraSettings.getValue(qt[i])) );
    }
    
}


void CameraInput::processLoop(){

    for (HashMap<ProcessLoop<cv::Mat, cv::Mat> *, bool>::Iterator i (process); i.next();){
        if(i.getKey()->lastCalculatedLatency > lastCalculatedLatency)
            lastCalculatedLatency=i.getKey()->lastCalculatedLatency;
        
        if(doubleBufferBit == i.getValue()){
            if(doubleBufferBit){
                i.getKey()->process(frame_1,currentTimeStamp);
            }else{
                i.getKey()->process(frame_0,currentTimeStamp);
            }
        }
    }

}

void CameraInput::registerProcess(ProcessLoop<cv::Mat , cv::Mat > * bufferProcess,bool doubleBuf){
    if (bufferProcess != NULL) {
        process.set(bufferProcess, doubleBuf);
    }
}

int CameraInput::numberOfCameras = 0;

//This function scans the cameras on the system and returns the number of cameras
int CameraInput::scanAvailableCameras(){
    bool cameraFound = true;
    int foundCameras = 0;
    
    while (cameraFound){
		cv::VideoCapture cam;
        if(cam.open(foundCameras)){
            if ( ! cam.isOpened() ) { DBG("--(!)Error opening video capture") }

            cam.release();
            DBG("found Camera" + juce::String(foundCameras));
            foundCameras++;
        } else {
            DBG("failed to find Camera" + juce::String(foundCameras));
            
            cameraFound = false;
        }
    }
    numberOfCameras = foundCameras;
    
    return foundCameras;
}

