/*
* gestureControlHelper.cpp / Gesture Control
*
* Triet Ngo / CS 8674 / Northeastern University
* Spring 2024 / Apr 25, 2024
*
*/

#include <stdio.h>
#include <iostream>
#include <cmath>

// SendInput only supported in Windows 2000 and later
#define WINVER 0x0500
#include <Windows.h>
#include <Winuser.h>

// Import OpenCV C++ Module
#include <opencv2/opencv.hpp>

// Import Helper Functions
#include "gestureControlHelper.hpp"


/* 
* This function refreshes the cursor temporarily to allow
* arrow key presses to register, assuming the program window does
* not start at (0, 0)
*/
void cursorRefreshTemp() {

    // Temporarily set cursor to (0, 0)
    SetCursorPos(0, 0);

    // Click to deselect current
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


/*
* This function presses the key on the active keyboard based on the argument
* Currently allows for UP, DOWN, LEFT, RIGHT, RETURN/ENTER, BACKSPACE keys
* Parameter:
*   const char* inputDir: input direction as a string
*/
void pressKey(const char* inputDir) {

    // Create Input Event
    INPUT ip{};

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Depending on direction, select the appropriate key
    if (strcmp(inputDir, "left") == 0) {
        ip.ki.wVk = VK_LEFT; // virtual-key code for the LEFT-ARROW key
    }

    else if (strcmp(inputDir, "right") == 0) {
        ip.ki.wVk = VK_RIGHT; // virtual-key code for the RIGHT-ARROW key
    }

    else if (strcmp(inputDir, "up") == 0) {
        ip.ki.wVk = VK_UP; // virtual-key code for the UP-ARROW key
    }

    else if (strcmp(inputDir, "down") == 0) {
        ip.ki.wVk = VK_DOWN; // virtual-key code for the DOWN-ARROW key
    }

    else if (strcmp(inputDir, "enter") == 0) {
        ip.ki.wVk = VK_RETURN; // virtual-key code for the RETURN key
    }

    // Key Press
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));

    // Release the key
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}


/*
* This function controls inputs based on hand movements. Gesture direction roughly dictates
* how the selection should move on the screen. For example, hand moving up is analogous to pressing the
* UP arrow key, and so on
* Parameters:
*   mouseCurPosX, mouseCurPosY: current mouse position on the screen
*   newMouseCurPosX, newMouseCurPosY: position on the screen as registered by the detection module
*/
void cursorControl(int mouseCurPosX, int mouseCurPosY, int newMouseCurPosX, int newMouseCurPosY) {

    // Changes in coords
    int dx = abs(mouseCurPosX - newMouseCurPosX);   // change in x-coordinate
    int dy = abs(mouseCurPosY - newMouseCurPosY);   // change in y-coordinate

    // Move left
    if (newMouseCurPosX > mouseCurPosX && dx > dy) {
        cursorRefreshTemp();
        pressKey("left");
        //cout << "Moved Left" << endl;
    }

    // Move right
    else if (newMouseCurPosX < mouseCurPosX && dx > dy) {
        cursorRefreshTemp();
        pressKey("right");
        //cout << "Moved Right" << endl;
    }

    // Move up
    else if (newMouseCurPosY < mouseCurPosY && dx < dy) {
        cursorRefreshTemp();
        pressKey("up");
        //cout << "Moved Up" << endl;
    }

    // Move down
    else if (newMouseCurPosY > mouseCurPosY && dx < dy) {
        cursorRefreshTemp();
        pressKey("down");
        //cout << "Moved Down" << endl;
    }

    // Set cursor to old pos
    SetCursorPos(newMouseCurPosX, newMouseCurPosY);

    mouseCurPosX = newMouseCurPosX;
    mouseCurPosY = newMouseCurPosY;
}
