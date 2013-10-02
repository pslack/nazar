//
//  NazarProject.h
//  Nazar
//
//  Created by Peter J Slack on 13-09-25.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#ifndef NAZARPROJECT_H_INCLUDED
#define NAZARPROJECT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//Messages

const String MESSAGE_TIMER_TICK ="msg_tmt";


//Timer IDs
const int SYSTEM_MONITOR_TIMER_ID = 0;
const int LATENCY_TIMER_ID =1;

//Globals

//T is input type , V is Type
template < class T, class V>

class ProcessLoop : public Thread{
    
public:
    ProcessLoop(juce::String myName, bool myFrameBuffer) : Thread(myName){
        processName=myName;
        frameBuffer = myFrameBuffer;
    }
    virtual void run() = 0;
    void process(T input_value, int64 ts){
        timeStamp=ts;
        inputValue = input_value;
        startThread();
    }
    ~ProcessLoop(){}
    
    int64 timeStamp;
    T inputValue;
    juce::String processName;
    bool frameBuffer;
protected:
    
};




//==============================================================================
/**
 Receives timer ticks
 
 Used by various classes, e.g. buttons when they are pressed, to tell listeners
 about something that's happened.
 
 */
class TimerListener
{
public:
    
    TimerListener(){}
    virtual ~TimerListener() {}
    /** Overridden by your subclass to receive the timer tick.
     
     by a call to 
     */
    virtual void timerTick(int64 ID) = 0;
    virtual void shutDownRequested() = 0;
    
};

class SystemTimer : public MultiTimer 
{   
public:
    
    
    SystemTimer();
    ~SystemTimer();
    void timerCallback (int timerID);
    
    void setLatency(int latency);
    int getLatency();
    void registerListener(int ID , TimerListener * listener);
    void removeListener(TimerListener * listener);
    void startShutDownTimerSequence();
    double startTimeStamp;
    void startTmers();
    void stopTmers();
    
    
protected:
    int64 currentTimeStamp;
    HashMap<TimerListener *,int> systemListeners;
    HashMap<TimerListener *,int> systemTimerGroup;
    bool iShouldShutTheApplication = false;
    int64 baseTime; // the timestamp when we booted the timer up
    //used as a relative base for our heartbeat
private:
    void shutTheSystemDown();
    int latency=150;
    
    
    
};

#include "opencv2/highgui/highgui.hpp"


class CameraInput : public Thread ,public TimerListener
{
public:
    static int numberOfCameras;
    CameraInput(juce::String name,int camera_ID, SystemTimer * sysTimer);
    ~CameraInput();
    void run();
    void shouldExit();
    static int scanAvailableCameras();
    void timerTick(int64 ID);
    void shutDownRequested();
    void registerProcess(ProcessLoop<cv::Mat, cv::Mat> * bufferProcess,bool doubleBuf);
protected:
    void processLoop();
    int errorCount = 0 ;
    SystemTimer * mySystemTimer=NULL;
    int cameraID=0;
    bool iShouldExit=false;
    cv::String windowName;
    PropertySet cameraSettings;
    PropertySet propertyNames;
    int64 currentTimeStamp;
    void loadCameraProperties();
    HashMap<ProcessLoop<cv::Mat,cv::Mat> * , bool> process;
    
private:
    bool doubleBufferBit=false;
    cv::VideoCapture capture;
    cv::Mat frame_0;
    cv::Mat frame_1;
    WaitableEvent cameraShutter;
    bool initialized = false;
    
    
};


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


class TargetTracker : public ProcessLoop<cv::Mat,cv::Mat> {
public:
    TargetTracker(juce::String myName ,bool myFrame) : ProcessLoop<cv::Mat, cv::Mat>(myName, myFrame){}
    ~TargetTracker(){}
    void run();
};

class EyeTracker : public ProcessLoop<cv::Mat,cv::Mat> {
public:
    EyeTracker(juce::String myName, bool myFrame) : ProcessLoop<cv::Mat, cv::Mat>(myName ,myFrame){}
    ~EyeTracker(){}
    void run();
};


/*
 ==============================================================================
 
 
 
 ==============================================================================
 */

//==============================================================================
class NazarApplication  : public JUCEApplication
{
public:
    //==============================================================================
    NazarApplication() {}
    
    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    const String getApplicationExecutablePath() { return (File::getSpecialLocation(File::SpecialLocationType::hostApplicationPath).getFullPathName());}
    
    bool moreThanOneInstanceAllowed()       { return false; }
    ScopedPointer<SystemTimer> sysTimer;
    
    //==============================================================================
    void initialise (const String& commandLine)
    {
        
        initCommandManager();
        
        // Add your application's initialisation code here..
        DBG(/*juce::String((int64)Thread::getCurrentThreadId()) +*/ ":  Main Thread"  );
        DBG(collectSystemInfo());
        
        sysTimer = new SystemTimer();
        
        int numCams = CameraInput::scanAvailableCameras();
        //        int numCams = 2;
        for(int i=0;i<numCams;i++){
            CameraInput * U = new CameraInput(String("Camera") + String(i),i,sysTimer);
            if(i==0){
                U->registerProcess(new TargetTracker(String("CompCamera") + String(i) + String("-buf1"),true), true);
                U->registerProcess(new TargetTracker(String("CompCamera") + String(i) + String("-buf2"),false), false);
            }
            if(i==1){
                U->registerProcess(new EyeTracker(String("EyeCamera") + String(i) + String("-buf1"), true), true);
                U->registerProcess(new EyeTracker(String("EyeCamera") + String(i) + String("-buf2"), false), false);
            
            }
        }
        
        
        sysTimer->startTmers();
        
        
    }
    
    void shutdown()
    {
        // Add your application's shutdown code here..
        
    }
    
    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        
        DBG(/*(int64)Thread::getCurrentThreadId() +*/": call to shutdown");
        
        sysTimer->startShutDownTimerSequence();
        
        
    }
    
    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }
    
    static NazarApplication& getApp()
    {
        NazarApplication* const app = dynamic_cast<NazarApplication*> (JUCEApplication::getInstance());
        jassert (app != nullptr);
        return *app;
    }
    
    
    static ApplicationCommandManager& getCommandManager()
    {
        ApplicationCommandManager* cm = NazarApplication::getApp().commandManager;
        jassert (cm != nullptr);
        return *cm;
    }
    
    
    //==============================================================================
    // this little function just demonstrates a few system info calls
    static String collectSystemInfo()
    {
        String systemInfo;
        
        systemInfo
        << "Time and date: " << Time::getCurrentTime().toString (true, true) << newLine
        
        << "User logon name: "  << SystemStats::getLogonName() << newLine
        << "Full user name: "   << SystemStats::getFullUserName() << newLine
        << "Host name: "        << SystemStats::getComputerName() << newLine
        << "Operating system: " << SystemStats::getOperatingSystemName() << newLine
        << "Locale: "           << SystemStats::getUserLanguage() << "-" << SystemStats::getUserRegion() << newLine
        
        << "Memory size: "    << SystemStats::getMemorySizeInMegabytes() << "MB" << newLine
        << "Number of CPUs: " << SystemStats::getNumCpus() << newLine
        << "CPU vendor: "     << SystemStats::getCpuVendor() << newLine
        << "CPU speed: "      << SystemStats::getCpuSpeedInMegaherz() << "MHz" << newLine
        << "CPU has MMX: "    << (SystemStats::hasMMX()   ? "yes" : "no") << newLine
        << "CPU has SSE: "    << (SystemStats::hasSSE()   ? "yes" : "no") << newLine
        << "CPU has SSE2: "   << (SystemStats::hasSSE2()  ? "yes" : "no") << newLine
        << "CPU has SSE3: "   << (SystemStats::hasSSE3()  ? "yes" : "no") << newLine
        << "CPU has 3DNOW: "  << (SystemStats::has3DNow() ? "yes" : "no") << newLine
        
        << "Found network card MAC addresses: " << getMacAddressList() << newLine
        << "Found IP addresses: " << getIPAddressList() << newLine
        
        << "Current working directory: "         << File::getCurrentWorkingDirectory().getFullPathName() << newLine
        << "Current executable file: "           << File::getSpecialLocation (File::currentExecutableFile).getFullPathName() << newLine
        << "Current application file: "          << File::getSpecialLocation (File::currentApplicationFile).getFullPathName() << newLine
        << "User home directory: "               << File::getSpecialLocation (File::userHomeDirectory).getFullPathName() << newLine
        << "User documents directory: "          << File::getSpecialLocation (File::userDocumentsDirectory).getFullPathName() << newLine
        << "User application data directory: "   << File::getSpecialLocation (File::userApplicationDataDirectory).getFullPathName() << newLine
        << "Common application data directory: " << File::getSpecialLocation (File::commonApplicationDataDirectory).getFullPathName() << newLine
        << "Temp directory: "                    << File::getSpecialLocation (File::tempDirectory).getFullPathName() << newLine
        << newLine;
        
        return systemInfo;
    }
    
    static String getMacAddressList()
    {
        Array <MACAddress> macAddresses;
        MACAddress::findAllAddresses (macAddresses);
        
        StringArray addressStrings;
        for (int i = 0; i < macAddresses.size(); ++i)
            addressStrings.add (macAddresses[i].toString());
        
        return addressStrings.joinIntoString (", ");
    }
    
    static String getIPAddressList()
    {
        Array <IPAddress> addresses;
        IPAddress::findAllAddresses (addresses);
        
        StringArray addressStrings;
        for (int i = 0; i < addresses.size(); ++i)
            addressStrings.add (addresses[i].toString());
        
        return addressStrings.joinIntoString (", ");
    }
    
    
private:
    ScopedPointer<ApplicationCommandManager> commandManager;

    void initCommandManager()
    {
        commandManager = new ApplicationCommandManager();
        commandManager->registerAllCommandsForTarget (this);
        
 
    }
    
};




#endif
