//
//  main.cpp
//  GestureControl
//
//  Created by Triết Ngô on 2/10/24.
//

#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/objdetect.hpp>
//#include "gestureControlMain.hpp"

using namespace std;
using namespace cv;

int main() {
    
    // Initialize img
    Mat img;

    // Init VideoCapture object cap(<cameraID>) or cap(<path to video>)
    int cameraMain = 0;

    VideoCapture cap(cameraMain);
    
    // Haar Cascade Detection Method
    // Load Cascade Model
    
    // Left hand model
    CascadeClassifier leftHandCascade;
    leftHandCascade.load("../Resources/lpalm.xml");
    
    // Fist model
    CascadeClassifier fistCascade;
    fistCascade.load("../Resources/fist.xml");
    
    // Check if loaded
    if (leftHandCascade.empty() || fistCascade.empty()) {
        cout << "XML files not loaded." << endl;
    }
    
    while (true) {
        cap.read(img);
        
        // Bounding boxes for left hand and fist
        vector<cv::Rect> leftHands;
        leftHandCascade.detectMultiScale(img, leftHands, 1.1, 5);
        
        // Bounding boxes for fist
        vector<cv::Rect> fists;
        fistCascade.detectMultiScale(img, fists, 1.1, 10);
        
        // Draw left hands
        for (int i = 0; i < leftHands.size(); i++) {
            rectangle(img, leftHands[i].tl(), leftHands[i].br(), Scalar(255, 0, 255), 2);
            
            // Put text above bound box
            putText(img, "Left Hand", {leftHands[i].x, leftHands[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1);
            
            // Print debug
            cout << "Left Hand" << " " << leftHands[i].x << " " << leftHands[i].y << endl;
        }
        
        // Draw fists
        for (int i = 0; i < fists.size(); i++) {
            rectangle(img, fists[i].tl(), fists[i].br(), Scalar(0, 255, 255), 2);
            
            // Put text above bound box
            putText(img, "Fist", {fists[i].x, fists[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255), 1);
            
            // Print debug
            cout << "Fist" << " " << fists[i].x << " " << fists[i].y << endl;
        }

        imshow("Image", img);
        waitKey(1);
    }

    return 0;

}
