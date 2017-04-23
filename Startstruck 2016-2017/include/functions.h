#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

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
void liftUp(int liftPotDesiredValue);
void liftDown(int liftPotDesiredValue);
void openPincers(int clawPotDesiredValue);
void closePincers(int clawPotDesiredValue);
void liftStop();
void pinceStop();
void driveStop();
void liftStop();
void pincerStop();
void driveForwardAndClosePincers(int encoder_value, int clawPot);
void autonOne(int flipDrive);


#endif
