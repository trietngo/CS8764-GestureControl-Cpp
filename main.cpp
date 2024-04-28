/*
* main.cpp / GestureControl
* 
* Triet Ngo / CS 8674 / Northeastern University
* Spring 2024 / Apr 25, 2024
* 
* Haar Cascade Hand Models created by Sandeep Sthapit: https://github.com/Sandeep-Sthapit/HandGestureDetection
*/

#include <stdio.h>
#include <iostream>
#include <cmath>

// SendInput only supported in Windows 2000 and later
#define WINVER 0x0500
#include <Windows.h>
#include <winuser.h>

// Import OpenCV C++ Module
#include <opencv2/opencv.hpp>

// Import header files containing helper functions
#include "gestureControlHelper.hpp"

// Define monitor resolution
#define monWidth 3840
#define monHeight 2160

using namespace std;
using namespace cv;

// Viewing window name
string WINDOW_STR = "Webcam";

// Main function that captures hand gestures to perform appropriate move and select actions
int main() {
    
    // Initialize img
    Mat img;

    // Init VideoCapture object cap(<cameraID>) or cap(<path to video>)
    int cameraMain = 0;

    VideoCapture cap(cameraMain);
    
    // Haar Cascade Detection Method
    // Load Cascade Model
    
    // Left hand model
    CascadeClassifier rightHandCascade;
    rightHandCascade.load("INSERT rpalm.xml LOCATION");
    
    // Fist model
    CascadeClassifier fistCascade;
    fistCascade.load("INSERT fist.xml LOCATION");
    
    // Check if loaded
    if (rightHandCascade.empty() || fistCascade.empty()) {
        cout << "XML files not loaded." << endl;
        exit(1);
    }

    // Set frame
    cap.set(cv::CAP_PROP_BUFFERSIZE, 3);
    cap.set(cv::CAP_PROP_FPS, 60);

    // While the camera is still capturing frame by frame
    while (true) {

        // Hide cursor
        ShowCursor(false);

        // Read and extract information from the current frame
        cap.read(img);
        
        // Detect right hand
        vector<cv::Rect> rightHands;
        rightHandCascade.detectMultiScale(img, rightHands, 1.3, 5, 0 | CASCADE_SCALE_IMAGE, Size(150, 150));
        
        // Detect fist
        vector<cv::Rect> fists;
        fistCascade.detectMultiScale(img, fists, 1.3, 5, 0 | CASCADE_SCALE_IMAGE, Size(150, 150));

        // Get prev mouse cursor
        POINT mousePos;

        if (!GetCursorPos(&mousePos)) {
            cout << "Cannot get mouse position" << endl;
        }

        int mouseCurPosX = mousePos.x;
        int mouseCurPosY = mousePos.y;
        
        // Draw right hand box
        for (int i = 0; i < rightHands.size(); i++) {
            rectangle(img, rightHands[i].tl(), rightHands[i].br(), Scalar(255, 0, 255), 2);
            
            // Put text above bound box
            putText(img, "Right Hand", {rightHands[i].x, rightHands[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1);
            
            // Print debug
            //cout << "Right Hand" << " " << rightHands[i].x << " " << rightHands[i].y << endl;

            // Control the selection based on current hand movements
            cursorControl(mouseCurPosX, mouseCurPosY, rightHands[i].x, rightHands[i].y);

            // Interval
            Sleep(300);
        }
        
        // Draw fists
        for (int i = 0; i < fists.size(); i++) {

            pressKey("enter");

            rectangle(img, fists[i].tl(), fists[i].br(), Scalar(0, 255, 255), 2);
            
            // Put text above bound box
            putText(img, "Fist", {fists[i].x, fists[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255), 1);
            
            // Print debug
            //cout << "Fist" << " " << fists[i].x << " " << fists[i].y << endl;

            // Interval
            Sleep(300);
            break;
        }

        // Show the stream
        imshow(WINDOW_STR, img);
        int key = waitKey(1);

        // Press q or ESC to quit
        if (key == 'q' || key == 27) {
            cap.release();
            destroyAllWindows();
            exit(1);
        }
    }

    return 0;

}
