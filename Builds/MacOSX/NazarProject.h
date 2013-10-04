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
#include "SettingDialog.h"

enum NAZAR_EVENTID{
    NAZAR_MOUSE_MOVE = 0x0000,
    NAZAR_MOUSE_RIGHT_CLICK = 0x0001,
    NAZAR_MOUSE_LEFT_CLICK = 0x0002,
    NAZAR_MOUSE_DOUBLE_CLICK = 0x0003
    
    
};

enum CommandIDs
{
    doCalibration              = 0x2000,
    showEyeTrackWindow         = 0x2001,
    showTargetTrackWindow      = 0x2002,
    setTransportPlay            = 0x2003,
    setTransportPause           = 0x2004
    
};


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
    double lastCalculatedLatency=0.0;
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
    double lastCalculatedLatency=0.0;
     
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
    void startTimers();
    void stopTimers();
    void setTransportState(bool isPlaying);
    
protected:
    int64 currentTimeStamp;
    HashMap<TimerListener *,int> systemListeners;
    HashMap<TimerListener *,int> systemTimerGroup;
    bool iShouldShutTheApplication = false;
    int64 baseTime; // the timestamp when we booted the timer up
    //used as a relative base for our heartbeat


private:
    void shutTheSystemDown();
    int latency=80;
    bool transportState;
};

#include "opencv2/highgui/highgui.hpp"


class NazarMouseEvent{
public:
    int64 timeStamp;
    int nazarEventID;
};

class MouseController : public Thread, public TimerListener{
    
public:
    MouseController() : Thread("oiii"){
        
    }
    
    void run(){
        rightClickMouse(0, 0);
    }
    void moveMouse(int x, int y);
    void rightClickMouse(int x, int y);
    void leftClickMouse(int x, int y);
    void doubleClickMouse(int x, int y);
    void leftClickMouseControl(int x, int y);
    void timerTick(int64 tick);
    void shutDownRequested(){
    }
    
    ~MouseController(){}
    int to(int x,int y);
    
private:
    int64 currentTimeStamp;
    int64 previousTimeStamp;
    
    void queryMouse();
    MouseInputSource mouseIn = Desktop::getInstance().getMainMouseSource();
    juce::Point<int> currentScreenPosition;
    int mouseTimerCount =0;
    
private:
    std::vector<NazarMouseEvent> mouseQueue;
    
};



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


//==============================================================================
#if JUCE_WINDOWS || JUCE_LINUX || JUCE_MAC

// Just add a simple icon to the Window system tray area..
class NazarTaskbarComponent  : public SystemTrayIconComponent,
private Timer
{
public:
    NazarTaskbarComponent()
    {
        setIconImage (createImageForIcon());
        setIconTooltip ("Juce Demo App!");
    }
    
    Image createImageForIcon()
    {
        Image icon (Image::RGB, 32, 32, true);
        
        Graphics g (icon);
        
        // This draws an icon which is just a square with a "j" in it..
        g.fillAll (Colours::lightblue);
        g.setColour (Colours::black);
        g.setFont (Font ((float) icon.getHeight(), Font::bold));
        g.drawText ("j", 0, 0, icon.getWidth(), icon.getHeight(), Justification::centred, false);
        
        return icon;
    }
    
    void mouseDown (const MouseEvent&) override
    {
        // On OSX, there can be problems launching a menu when we're not the foreground
        // process, so just in case, we'll first make our process active, and then use a
        // timer to wait a moment before opening our menu, which gives the OS some time to
        // get its act together and bring our windows to the front.
        
        Process::makeForegroundProcess();
        startTimer (50);
    }
    
    void timerCallback() override
    {
        stopTimer();
        
        PopupMenu m;
        m.addItem(1,"Goodbye");
        m.addItem(2,"Settings");
        m.addItem(3,"Calibrate");
        
        // It's always better to open menus asynchronously when possible.
        m.showMenuAsync (PopupMenu::Options(),
                         ModalCallbackFunction::forComponent (menuInvocationCallback, this));
    }
    
    // This is invoked when the menu is clicked or dismissed
    static void menuInvocationCallback (int chosenItemID, NazarTaskbarComponent*)
    {
        
        switch (chosenItemID) {
            case 1:
                JUCEApplication::getInstance()->systemRequestedQuit();
                break;
            case 2:
                JUCEApplication::getInstance()->invokeDirectly(CommandIDs::doCalibration, true);
            default:
                break;
        };
            
        
    }
};

#endif




/*
 ==============================================================================
 
 
 
 ==============================================================================
 */

//==============================================================================
class NazarApplication  : public JUCEApplication , public MenuBarModel, public MenuBarModelListener, public MouseListener
{
public:
    //==============================================================================
    NazarApplication() {}
    
    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    const String getApplicationExecutablePath() { return (File::getSpecialLocation(File::SpecialLocationType::hostApplicationPath).getFullPathName());}
    
    bool moreThanOneInstanceAllowed()       { return false; }
    ScopedPointer<SystemTimer> sysTimer;
    ScopedPointer<SettingDialog> calibrationWindow;
    ScopedPointer<NazarTaskbarComponent> sysTrayWindow;
    MouseController * systemMouseController;
    
    int mainScreenWidth = 640;
    int mainScreenHeight = 480;
    
    
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
        
        
        sysTimer->startTimers();
        
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
        
        MenuBarModel * mm = MenuBarModel::getMacMainMenu ();
        
        //        MenuBarModel::setMacMainMenu(this);
        if(mm == this)
            
            DBG("Fuck me I'm me");
        
#endif
        sysTrayWindow = new NazarTaskbarComponent();
        sysTrayWindow->setVisible(true);
        
        calibrationWindow=new SettingDialog();
//        
       calibrationWindow->setVisible(false);
        
        Desktop::getInstance().addGlobalMouseListener(this);
        
        systemMouseController = new MouseController();
        
        
        sysTimer -> registerListener(LATENCY_TIMER_ID, systemMouseController);
       systemMouseController->startThread();
        
//        systemMouseController->leftClickMouseControl(1048, 255);
//        systemMouseController->leftClickMouseControl(1048, 747);
//        systemMouseController->leftClickMouseControl(1532, 255);
//        systemMouseController->leftClickMouseControl(1532, 747);
        
    }
    
    void shutdown()
    {
        // Add your application's shutdown code here..
        
        Desktop::getInstance().removeGlobalMouseListener(this);
        
    }
    
    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        
        DBG(/*(int64)Thread::getCurrentThreadId() +*/": call to shutdown");
        
        sysTimer->removeListener(systemMouseController);
        
        sysTimer->startShutDownTimerSequence();
        
        
    }
    
    
    void postTargetTrackerPoint(float x_bar, float y_bar, int64 TS){
       DBG("T :" + String(x_bar) + ":" + String(y_bar) + ":" + String(TS) );
    }
    
    void postEyeTrackerPoint(float x_bar, float y_bar, int64 TS){
        DBG("E :" + String(x_bar) + ":" + String(y_bar) + ":" + String(TS) );
        
    }
    
    void postMouseLocation(float x, float y , int64 TS){
        DBG("M :" + String(x) + ":" + String(y) + ":" + String(TS) );
   
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
    
    
    
    //// COMMANDS
    
    void getAllCommands (Array <CommandID>& commands)
    {
        // this returns the set of all commands that this target can perform..
        const CommandID ids[] = { doCalibration,
            showEyeTrackWindow,
            showTargetTrackWindow
        };
        
        commands.addArray (ids, numElementsInArray (ids));
    }
    
    // This method is used when something needs to find out the details about one of the commands
    // that this object can perform..
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
    {
        
        const String viewCategory ("View");
        const String settingsCategory ("Settings");

        
        switch (commandID)
        {
            case doCalibration:
                result.setInfo ("Calibration","run the calibration sequence", settingsCategory, 0);
                result.setTicked (true);
                result.addDefaultKeypress ('1', ModifierKeys::commandModifier);

                break;
                
            case showEyeTrackWindow:
                result.setInfo ("View Eye","Show the eye tracking window", viewCategory, 0);
                result.setTicked (eyeWindowVisible);
                result.addDefaultKeypress ('2', ModifierKeys::commandModifier);
                
                break;
                
            case showTargetTrackWindow:
                result.setInfo ("View Target","show the target view window", viewCategory, 0);
                result.setTicked (targetWindowVisible);
                result.addDefaultKeypress ('3', ModifierKeys::commandModifier);
                
                break;
                
            default:
                break;
        };
    }
    
    // this is the ApplicationCommandTarget method that is used to actually perform one of our commands..
    bool perform (const InvocationInfo& info)
    {
        switch (info.commandID)
        {
            case doCalibration:
                DBG("Calibration ole");
                calibrationWindow->setVisible(true);
                break;
            case showEyeTrackWindow:
                DBG("show eye");
                break;
            case showTargetTrackWindow:
                DBG("show face");
                break;
               
            default:
                return false;
        };
        
        return true;
    }
    
    
    
    ///// MOUSE INPUT
    
    
    void 	mouseMove (const MouseEvent &event){ DBG("f'in mouse moved");}
 	//Called when the mouse moves inside a component.
    
    void 	mouseEnter (const MouseEvent &event){}
 	//Called when the mouse first enters a component.
    
    void 	mouseExit (const MouseEvent &event){}
 	//Called when the mouse moves out of a component.
    
    void 	mouseDown (const MouseEvent &event){}
 	//Called when a mouse button is pressed.
    
    void 	mouseDrag (const MouseEvent &event){}
 	//Called when the mouse is moved while a button is held down.
    
    void 	mouseUp (const MouseEvent &event){}
    //Called when a mouse button is released.
    
    void 	mouseDoubleClick (const MouseEvent &event){}
    //Called when a mouse button has been double-clicked on a component.
    
    void 	mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel){}
    //Called when the mouse-wheel is moved.
    

    
    
    ///// MENUS
    
    StringArray getMenuBarNames()
    {
        const char* const names[] = { "Calibration", "View", nullptr };
        
        return StringArray (names);
    }
    
    PopupMenu getMenuForIndex (int menuIndex, const String& /*menuName*/)
    {
        
        PopupMenu menu;
        
        if (menuIndex == 0)
        {
            menu.addCommandItem (commandManager, doCalibration);
        }
        else if (menuIndex == 1)
        {
            menu.addCommandItem (commandManager, showEyeTrackWindow);
            menu.addCommandItem (commandManager, showTargetTrackWindow);
        }
        
        return menu;
    }
    
    void menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/)
    {
        // most of our menu items are invoked automatically as commands, but we can handle the
        // other special cases here..
        

    }
    
    void 	menuBarItemsChanged (MenuBarModel *menuBarModel){}
    
    void 	menuCommandInvoked (MenuBarModel *menuBarModel, const ApplicationCommandTarget::InvocationInfo &info){}
    
    //==============================================================================
     
    
private:
    
    bool eyeWindowVisible = true;
    bool targetWindowVisible = true;
     
    ScopedPointer<ApplicationCommandManager> commandManager;

    void initCommandManager()
    {
        commandManager = new ApplicationCommandManager();
        commandManager->registerAllCommandsForTarget (this);
        
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
        
        MenuBarModel * mm = MenuBarModel::getMacMainMenu ();
        
        MenuBarModel::setMacMainMenu(nullptr);
        if(mm == this)

            DBG("Fuck me I'm me");
        
#endif

        

    }
    

};





#endif
