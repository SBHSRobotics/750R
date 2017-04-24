/*
 * variables.c
 *
 *  Created on: Jan 19, 2017
 *      Author: Shivam Agrawal
 */

#include "variables.h"


//LEDs
int led_Drive = 4;
int led_Lift = 9;
int led_Pincer = 6;

 // potentiometers
int pince_pot = 1;
int lift_pot = 10;

// lift motors
int left_lift_Motor1 = 2;
int left_lift_Motor2 = 3;// Y-cabled
int right_lift_Motor3 = 8;
int right_lift_Motor4 = 9;// Y-cabled
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



// drive ports
int front_left_drive = 4;
int front_right_drive = 5;
int back_left_drive = 6;
int back_right_drive = 7;
// pincer ports+
int pincer_left = 1;
int pincer_right = 10;
// operator control functions
int joystickAxes(int channel){
	if (abs(joystickGetAnalog(1,channel))>15){
		return joystickGetAnalog(1, channel);

	}
	else {
		return  0;
	}// This function only returns the joystick value if it passes the threshold

}
void drive(int y, int x){
	motorSet(front_left_drive,  -y - x );
	motorSet(front_right_drive,   y - x );
	motorSet(back_left_drive,   -y - x );
	motorSet(back_right_drive,   - y + x );

}
void lift(){
	if (joystickGetDigital(1, 6, JOY_UP)){// lift goes up
//		if(analogRead(lift_pot > 4000)){// if the lift is vertical
//			motorSet(pincer_right, 127);// open the pincers
//			motorSet(pincer_left, -127);
//			motorSet(left_lift_Motor1, 0);// stop the lift
//			motorSet(left_lift_Motor2, 0);
//			motorSet(right_lift_Motor3, 0);
//			motorSet(right_lift_Motor4, 0);
//		}

		motorSet(left_lift_Motor1, -127);//  lift goes up
		motorSet(left_lift_Motor2, 127);
		motorSet(right_lift_Motor3, -127);
		motorSet(right_lift_Motor4, 127);
		pinMode(led_Lift,OUTPUT);

	}
	else if (joystickGetDigital(1, 6, JOY_DOWN)){
		motorSet(left_lift_Motor1, 127);
		motorSet(left_lift_Motor2, -127);
		motorSet(right_lift_Motor3, 127);
		motorSet(right_lift_Motor4, -127);
		pinMode(led_Lift,OUTPUT);
	}
	else{
		motorSet(left_lift_Motor1, 0);
		motorSet(left_lift_Motor2, 0);
		motorSet(right_lift_Motor3, 0);
		motorSet(right_lift_Motor4, 0);
		pinMode(led_Lift,INPUT);
	}

}
void pincers(){
	if (joystickGetDigital(1, 5, JOY_UP)){// close claw
		if (analogRead(pince_pot) < 4096){
			// we want to change speeds at a certain angle
			// that angle is 224
			// if less than 224 degrees, then go full speed
			motorSet(pincer_right, -127);
			motorSet(pincer_left, -127);
			pinMode(led_Pincer,OUTPUT);
		}
		else{
			// otherwise go at a lower speed
			// will help with motor stalling when trying to hold stars and cubes

			motorSet(pincer_right, -50);
			motorSet(pincer_left, -50);
		}
	}
		else if (joystickGetDigital(1, 5, JOY_DOWN)){// open claw
					motorSet(pincer_right, 127);
					motorSet(pincer_left, 127);
					pinMode(led_Pincer,OUTPUT);
		}


	else {
		motorSet(pincer_right, 0);
		motorSet(pincer_left, 0);
		pinMode(led_Pincer,INPUT);
	}

}
// autonomous functions

void driveForward(int encoder_value){
	while((encoderGet(frontLeftEncoder)+ encoderGet(frontRightEncoder))/2 < encoder_value){
		motorSet(front_left_drive,  -127);
		motorSet(front_right_drive,   127);
		motorSet(back_left_drive,   -127);
		motorSet(back_right_drive,   -127);
	}
	encoderReset(frontLeftEncoder);
	encoderReset(frontRightEncoder);
}

void driveBackward(int encoder_value){
	while((encoderGet(frontLeftEncoder)+ encoderGet(frontRightEncoder))/2 > -1*(encoder_value)){
		motorSet(front_left_drive,  127);
		motorSet(front_right_drive,  - 127);
		motorSet(back_left_drive,   127);
		motorSet(back_right_drive,   127);
	}
	encoderReset(frontLeftEncoder);
	encoderReset(frontRightEncoder);
}

void turnRight(int encoder_value){
	while((encoderGet(frontLeftEncoder) -  encoderGet(frontRightEncoder))/2 > encoder_value){
		motorSet(front_left_drive,  -127);
		motorSet(front_right_drive,  - 127);
		motorSet(back_left_drive,   -127);
		motorSet(back_right_drive,   127);
	}
	encoderReset(frontLeftEncoder);
	encoderReset(frontRightEncoder);
}
void turnLeft(int encoder_value){
	while(((-1*encoderGet(frontLeftEncoder)) +  encoderGet(frontRightEncoder))/2 > encoder_value){
		motorSet(front_left_drive,  127);
		motorSet(front_right_drive,   127);
		motorSet(back_left_drive,   127);
		motorSet(back_right_drive,  - 127);
	}
	encoderReset(frontLeftEncoder);
	encoderReset(frontRightEncoder);
}
void liftStop(){
	motorSet(left_lift_Motor1, 0);
	motorSet(left_lift_Motor2, 0);
	motorSet(right_lift_Motor3, 0);
	motorSet(right_lift_Motor4, 0);
}

// time based functions
void openPincers(int x){
	motorSet(pincer_right, -127);
	motorSet(pincer_left, -127);
	delay(x);
}
void closePincers(int x){
	motorSet(pincer_right, 127);
	motorSet(pincer_left, 127);
	delay(x);
}
void liftUp(int x){
	/*if(analogRead(lift_pot < 4000)){// if the lift is vertical
		motorSet(pincer_right, 127);// open the pincers
			motorSet(pincer_left, -127);
		motorSet(left_lift_Motor1, 0);// stop the lift
		motorSet(left_lift_Motor2, 0);
		motorSet(right_lift_Motor3, 0);
		motorSet(right_lift_Motor4, 0);
	}*/
	motorSet(left_lift_Motor1, -127);
	motorSet(left_lift_Motor2, -127);
	motorSet(right_lift_Motor3, 127);
	motorSet(right_lift_Motor4, 127);
	delay(x);
}
void liftDown(int x){
	motorSet(left_lift_Motor1, 127);
	motorSet(left_lift_Motor2, 127);
	motorSet(right_lift_Motor3, -127);
	motorSet(right_lift_Motor4, -127);
	delay(x);
}
void driveForwardTime(int x){
    motorSet(front_left_drive, 127);
    motorSet((front_right_drive), -127);
    motorSet(back_left_drive, 127);
    motorSet(back_right_drive, -127);
    delay(x);
}
void driveBackwardTime(int x){
    motorSet(front_left_drive, -127);
    motorSet((front_right_drive), 127);
    motorSet(back_left_drive, -127);
    motorSet(back_right_drive, 127);
    delay(x);
}

void turn_Right(int x){
    motorSet(front_left_drive, 127);
    motorSet((front_right_drive), 127);
    motorSet(back_left_drive, 127);
    motorSet(back_right_drive, 127);
    delay(x);
}
void turn_Left(int x){
    motorSet(front_left_drive, -127);
    motorSet((front_right_drive), -127);
    motorSet(back_left_drive, -127);
    motorSet(back_right_drive, -127);
    delay(x);
}
void right_auton(){


}
void left_auton(){


}
