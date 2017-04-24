/*
 * functions.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Shivam Agrawal
 */

#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_


#include "main.h"

int joystickAxes(int channel);
void drive(int y, int x);
void lift();
void pincers();
void pincersCorrect();

// autonomous functions
void driveForward(int encoder_value);
void driveBackward(int encoder_value);
void turnRight(int encoder_value);
void turnLeft(int enocder_value);
void liftUp(int x);
void liftDown(int x);
void openPincers(int x);
void closePincers(int x);
void liftStop();
void pinceStop();
void left_auton();
void right_auton();

//time based auton
void driveForwardTime(int x);
void driveBackwardTime(int x);
void turn_Right(int x);
void turn_Left(int x);



#endif /* INCLUDE_FUNCTIONS_H_ */
