#ifndef VARIABELS_H_
#define VARIABLES_H_

#include "main.h"
//LEDs
int led_Drive;
int led_Lift;
int led_Pincer;

// potentiometers
int pince_pot;
int lift_pot;
// lift motors
int left_lift_Motor1;
int left_lift_Motor2;
int right_lift_Motor3;
int right_lift_Motor4;
// encoder ports
int front_left_encoder_top;
int front_left_encoder_bottom;
int front_right_encoder_top;
int front_right_encoder_bottom;
int  back_left_encoder_top;
int  back_left_encoder_bottom;
int back_right_encoder_top;
int back_right_encoder_bottom;
// encoders
Encoder frontLeftEncoder;
Encoder frontRightEncoder;
Encoder backLeftEncoder;
Encoder backRightEncoder;
// gyroscope
Gyro gyro;
int flipTurns;
// drive ports
int front_left_drive ;
int front_right_drive;
int back_left_drive;
int back_right_drive ;
// pincer ports
int pincer_left ;
int pincer_right;



#endif
