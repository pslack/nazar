//
//  NazarProject.h
//  Nazar
//
//  Created by Peter J Slack on 13-09-25.
//  Copyright (c) 2013 Nazar Project. All rights reserved.
//

#ifndef NAZARPROJECT_H_INCLUDED
#define NAZARPROJECT_H_INCLUDED

#include "Global.h"

/*
 ==============================================================================
 
 
 
 ==============================================================================
 */

//==============================================================================
class NazarApplication  : public JUCEApplication , public MenuBarModel, public MenuBarModelListener, public MouseListener
{
public:
    //==============================================================================
    NazarApplication() {
	  mainScreenWidth = 640;
      mainScreenHeight = 480;
	 eyeWindowVisible = true;
    targetWindowVisible = true;
    trainingMode = false;
    transport = false; //fale = pause, true =play
	}
    
    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    const String getApplicationExecutablePath() { return (File::getSpecialLocation(File::SpecialLocationType::hostApplicationPath).getFullPathName());}
    
    bool moreThanOneInstanceAllowed()       { return false; }
    SystemTimer * sysTimer;
    ScopedPointer<SettingDialog> calibrationWindow;
    ScopedPointer<NazarTaskbarComponent> sysTrayWindow;
    ScopedPointer<NeuralNetCalibration> calibratorANN;
    
    MouseController * systemMouseController;
    
    int mainScreenWidth;
    int mainScreenHeight;
    
    
    //==============================================================================
    void initialise (const String& commandLine)
    {
        
        initCommandManager();
        
        // Add your application's initialisation code here..
        DBG(/*juce::String((juce::int64)Thread::getCurrentThreadId()) +*/ ":  Main Thread"  );
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
        
        
        
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
        
        MenuBarModel * mm = MenuBarModel::getMacMainMenu ();
        
        //        MenuBarModel::setMacMainMenu(this);
             
          
        
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
        
        
        calibratorANN = new NeuralNetCalibration("veyyy",sysTimer);
        sysTimer -> registerListener(LATENCY_TIMER_ID, calibratorANN);
        
        sysTimer->startTimers();
        
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
    
    void clearTrainingData(){
    
       mouseInputTrainingData.clear();
       targetInputTrainingData.clear();
        eyeInputTrainingData.clear();

    }
    
    
    void beginLearnMode(){
        calibratorANN->setTrained(false);
        clearTrainingData();
        trainingMode=true;
    }
    
    void postTargetTrackerPoint(float x_bar, float y_bar, juce::int64 TS){
       //DBG("T :" + String(x_bar) + ":" + String(y_bar) + ":" + String(TS) );
        if(trainingMode){
            if (targetInputTrainingData.size() == MAX_TRAINING_POINTS){
                trainNeuralNet();
            }else {
                targetInputTrainingData.set(TS,cv::Point2f(x_bar,y_bar));
            }
        }else {
            if(calibratorANN->isBrainTrained())
            targetInputData.set(TS,cv::Point2f(x_bar,y_bar));
        
        }
    }
    
    void postEyeTrackerPoint(float x_bar, float y_bar, juce::int64 TS){
        //DBG("E :" + String(x_bar) + ":" + String(y_bar) + ":" + String(TS) );
        if(trainingMode){
           
            if (eyeInputTrainingData.size() == MAX_TRAINING_POINTS){
                trainNeuralNet();
            } else {
                eyeInputTrainingData.set(TS, cv::Point2f(x_bar,y_bar));
            }
        }else{
            if(calibratorANN->isBrainTrained())
                eyeInputData.set(TS, cv::Point2f(x_bar,y_bar));
        
        
        }
            
        return;
    }
    
    void postMouseLocation(float x, float y , juce::int64 TS){
       
        if(trainingMode){
            if (mouseInputTrainingData.size() == MAX_TRAINING_POINTS){
                trainNeuralNet();
            }else{
                DBG("M :" + String(x) + ":" + String(y) + ":" + String(TS) );
        
                mouseInputTrainingData.set(TS, cv::Point2f(x,y));
            }
        }else{
        }
   
    }
    
    void brainMousePost(float x, float y , juce::int64 TS){
        systemMouseController->moveMouse(x, y);
    
    }
    
    void trainNeuralNet(){
        trainingMode=false;
        calibratorANN->train();
        DBG("TRAINING COMPLETE");

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
    
    
    /////////// ALN
    
    HashMap<juce::int64, cv::Point2f> * getMouseTrainingData(){
        return (&mouseInputTrainingData);
    }
    HashMap<juce::int64, cv::Point2f> * getTargetTrainingData(){
        return (&targetInputTrainingData);
    }
    HashMap<juce::int64, cv::Point2f> * getEyeTrainingData(){
        return (&eyeInputTrainingData);
    }
    HashMap<juce::int64, cv::Point2f> * getTargetData(){
        return (&targetInputData);
    }
    HashMap<juce::int64, cv::Point2f> * getEyeData(){
        return (&eyeInputData);
    }
    
    void setTraining(bool setTrainingBit){
        trainingMode = setTrainingBit;
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
    
    bool eyeWindowVisible;
    bool targetWindowVisible;
     
    ScopedPointer<ApplicationCommandManager> commandManager;

    HashMap<juce::int64, cv::Point2f> mouseInputTrainingData;
    HashMap<juce::int64,cv::Point2f> targetInputTrainingData;
    HashMap<juce::int64,cv::Point2f> eyeInputTrainingData;

    HashMap<juce::int64, cv::Point2f> eyeInputData;
    HashMap<juce::int64,cv::Point2f> targetInputData;

    
    bool trainingMode;
    bool transport; //fale = pause, true =play
    
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
