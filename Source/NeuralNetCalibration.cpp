//
//  NeuralNetCalibration.cpp
//  Nazar
//
//  Created by Peter J Slack on 2013-10-04.
//
//

#include "NazarProject.h"

NeuralNetCalibration::NeuralNetCalibration() : Thread("veyyy"){

    //The matrix representation of our ANN. We'll have four layers.
    CvMat* neuralLayers = cvCreateMat(4, 1, CV_32SC1);
    
    CvMat  neuralLayers1;
    
    cvGetRows(neuralLayers, &neuralLayers1, 0, 4);
    
    //Setting the number of neurons on each layer of the ANN
    /*
     We have in Layer 1: 4 neurons (4 inputs)
     Layer 2: 5 neurons (hidden layer)
     Layer 3: 5 neurons (hidden layer)
     Layer 4: 2 neurons (2 output)
     */
    cvSet1D(&neuralLayers1, 0, cvScalar(4));
    cvSet1D(&neuralLayers1, 1, cvScalar(5));
    cvSet1D(&neuralLayers1, 2, cvScalar(5));
    cvSet1D(&neuralLayers1, 3, cvScalar(2));

    
    machineBrain.create(neuralLayers);
    
}



NeuralNetCalibration::~NeuralNetCalibration(){}




void NeuralNetCalibration::process(){
    cv::Point2f eyeP;
    cv::Point2f targetP;
    NazarApplication * app = (NazarApplication *)JUCEApplication::getInstance();

    const MessageManagerLock mmLock;
    // the event loop will now be locked so it's safe to make a few calls..
    HashMap<int64, cv::Point2f> * eyeData = app->getEyeData();
    HashMap<int64, cv::Point2f> * targetData = app->getTargetData();
    
    if(eyeData->contains(previousTick)){
        eyeP = eyeData->operator[](previousTick);
        eyeData->remove(previousTick);
    }else{
        if(targetData->contains(previousTick))
            targetData->remove(previousTick);
    
        return;
    }
    
    
    if(targetData->contains(previousTick)){
        targetP = targetData->operator[](previousTick);
    }else{
        eyeData->remove(previousTick);

        return;
    }
        
    
    eye_x = eyeP.x; eye_y=eyeP.y; target_x=targetP.x; target_y=targetP.y;
    startThread();

}

void NeuralNetCalibration::train(){
    
    isTrained=false;
    
    NazarApplication * app = (NazarApplication *)JUCEApplication::getInstance();

 
    
    HashMap<int64, cv::Point2f> * mouseData = app->getMouseTrainingData();
    HashMap<int64, cv::Point2f> * eyeData = app->getEyeTrainingData();
    HashMap<int64, cv::Point2f> * targetData = app->getTargetTrainingData();
    
    float td[MAX_TRAINING_POINTS][6];
    cv::Point2f mouseP;
    cv::Point2f eyeP;
    cv::Point2f targetP;
    
    
    int train_sample_count = 0;
    //determine how many points we have
    for (HashMap<int64, cv::Point2f>::Iterator i (* mouseData); i.next();){
        int64 tkey = i.getKey();
        //only if we have points for eye and tracker
        if(eyeData->contains(tkey) && targetData->contains(tkey)){
        
            mouseP = i.getValue();
            eyeP = eyeData->operator[](tkey);
            targetP = targetData->operator[](tkey);
            td[train_sample_count][0]=eyeP.x;
            td[train_sample_count][1]=eyeP.y;
            td[train_sample_count][2]=targetP.x;
            td[train_sample_count][3]=targetP.y;
            td[train_sample_count][4]=mouseP.x;
            td[train_sample_count][5]=mouseP.y;
            
            train_sample_count++;
        }
    }
    
    
    //Input data samples. Matrix of order (train_sample_count x 4)
    CvMat* trainData = cvCreateMat(train_sample_count, 4, CV_32FC1);
    
    //Output data samples. Matrix of order (train_sample_count x 2)
    CvMat* trainClasses = cvCreateMat(train_sample_count, 2, CV_32FC1);
    
    //The weight of each training data sample. We'll later set all to equal weights.
    CvMat* sampleWts = cvCreateMat(train_sample_count, 2, CV_32FC1);

    CvMat trainData1, trainClasses1, neuralLayers1, sampleWts1;
    
    cvGetRows(trainData, &trainData1, 0, train_sample_count);
    cvGetRows(trainClasses, &trainClasses1, 0, train_sample_count);
    cvGetRows(trainClasses, &trainClasses1, 0, train_sample_count);
    cvGetRows(sampleWts, &sampleWts1, 0, train_sample_count);
    
    
    //Assemble the ML training data.
    for (int i=0; i<train_sample_count; i++)
    {
        //Input 1
        cvSetReal2D(&trainData1, i, 0, td[i][0]);
        //Input 2
        cvSetReal2D(&trainData1, i, 1, td[i][1]);
        //Input 3
        cvSetReal2D(&trainData1, i, 2, td[i][2]);
        //Input 4
        cvSetReal2D(&trainData1, i, 3, td[i][3]);
        //Output 1
        cvSetReal2D(&trainClasses1, i,0, td[i][4]);
        //Output 2
        cvSetReal2D(&trainClasses1, i,1, td[i][5]);
        //Weight (setting everything to 1)
        cvSetReal2D(&sampleWts1, i,0, 1);
        //Weight (setting everything to 1)
        cvSetReal2D(&sampleWts1, i,1, 1);
        //Weight (setting everything to 1)

        
    }
    
    machineBrain.train(
                       trainData,
                       trainClasses,
                       sampleWts,
                       0,
                       CvANN_MLP_TrainParams(
                                             cvTermCriteria(
                                                            CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
                                                            100000,
                                                            1.0
                                                            ),
                                             CvANN_MLP_TrainParams::BACKPROP,
                                             0.01,
                                             0.05
                                             )
                       );

    isTrained=true;
    
}

void NeuralNetCalibration::run(){

    cv::Point2f g = predict(eye_x, eye_y, target_x, target_y);
    DBG("ANN: x" + String(g.x) + " y:" + String(g.y));
    
}


void NeuralNetCalibration::timerTick(int64 ID){

    if(currentTick!=0)
        previousTick = currentTick;
    
    currentTick=ID;
    
    if(previousTick!=0 && isTrained)
        process();
    

}

cv::Point2f NeuralNetCalibration::predict(float eye_x,float eye_y,float tracker_x, float tracker_y){

    cv::Point2f myGuess;
    
    float _sample[4];
    CvMat sample = cvMat(1, 4, CV_32FC1, _sample);
    float _predout[2];
    CvMat predout = cvMat(1, 2, CV_32FC1, _predout);
    sample.data.fl[0] = eye_x;
    sample.data.fl[1] = eye_y;
    sample.data.fl[2] = tracker_x;
    sample.data.fl[3] = tracker_y;
    
    
    machineBrain.predict(&sample, &predout);

    myGuess.x = _predout[0];
    myGuess.y = _predout[1];
    
    
    return myGuess;

}
