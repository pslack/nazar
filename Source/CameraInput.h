#ifndef CAMERAINPUT_H_INCLUDED
#define CAMERAINPUT_H_INCLUDED



class CameraInput : public Thread ,public TimerListener
{
public:
    static int numberOfCameras;
    CameraInput(juce::String name,int camera_ID, SystemTimer * sysTimer);
    ~CameraInput();
    void run();
    void shouldExit();
    static int scanAvailableCameras();
    void timerTick(juce::int64 ID);
    void shutDownRequested();
    void registerProcess(ProcessLoop<cv::Mat, cv::Mat> * bufferProcess,bool doubleBuf);
protected:
    void processLoop();
    int errorCount;
    SystemTimer * mySystemTimer;
    int cameraID;
    bool iShouldExit;
    cv::String windowName;
    PropertySet cameraSettings;
    PropertySet propertyNames;
    juce::int64 currentTimeStamp;
    void loadCameraProperties();
    HashMap<ProcessLoop<cv::Mat,cv::Mat> * , bool> process;
    
private:
    bool doubleBufferBit;
    cv::VideoCapture capture;
    cv::Mat frame_0;
    cv::Mat frame_1;
    WaitableEvent cameraShutter;
    bool initialized;
    
    
};



#endif