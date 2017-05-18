#include "variables.h"

//LEDs
int led_Drive = 4;
int led_Lift = 9;
int led_Pincer = 6;

 // potentiometers
int pince_pot = 1;
int lift_pot = 2;

// lift motors
int left_lift_Motor1 = 2;
int left_lift_Motor2 = 3;// Y-cabled
int right_lift_Motor3 = 8;
int right_lift_Motor4 = 10;// Y-cabled
// encoder ports
int front_left_encoder_top = 1;
int front_left_encoder_bottom = 2;
int front_right_encoder_top = 3;
int front_right_encoder_bottom = 4;
int  back_left_encoder_top = 5;
int  back_left_encoder_bottom = 6;
int back_right_encoder_top = 7;
int back_right_encoder_bottom = 8;
// encoders
Encoder frontLeftEncoder;
Encoder frontRightEncoder;
Encoder backLeftEncoder;
Encoder backRightEncoder;
// gyroscope
Gyro gyro;

int flipTurns = 1;

// drive ports
int front_left_drive = 4;
int front_right_drive = 5;
int back_left_drive = 6;
int back_right_drive = 7;
// pincer ports+
int pincer_left = 9;
int pincer_right = 0;
