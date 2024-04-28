/*
* gestureControlHelper.hpp / Gesture Control
* 
* Triet Ngo / CS 8674 / Northeastern University
* Spring 2024 / Apr 25, 2024
* 
*/

#ifndef GESTURE_HELPER_HPP
#define GESTURE_HELPER_HPP

void cursorRefreshTemp();

void pressKey(const char* inputDir);

void cursorControl(int mouseCurPosX, int mouseCurPosY, int newMouseCurPosX, int newMouseCurPosY);

#endif // GESTURE_HELPER_HPP
