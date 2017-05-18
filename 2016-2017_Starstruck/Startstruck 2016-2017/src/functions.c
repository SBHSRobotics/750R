
/*
 * functions.c
 *
 *  Created on: Feb 23, 2017
 *      Author: zains
 */
#include "functions.h"
#include "variables.h"
#include "lcd.h"
int joystickAxes(int channel){
	if (abs(joystickGetAnalog(1,channel))>15){
		return joystickGetAnalog(1, channel);

	}
	else {
		return  0;
	}// This function only returns the joystick value if it passes the threshold

}
void drive(int y, int x){
	motorSet(front_left_drive,  y + x );
	motorSet(front_right_drive,  -y + x );
	motorSet(back_left_drive,  y + x );
	motorSet(back_right_drive,   - y + x );

}
void lift(){
	if (joystickGetDigital(2, 6, JOY_UP)){// lift goes up
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
	else if (joystickGetDigital(2, 6, JOY_DOWN)){
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
	if (joystickGetDigital(2, 5, JOY_UP)){// close claw
		//if ((analogRead(pince_pot_left) + analogRead(pince_pot_right))/2 < 4096){
			// we want to change speeds at a certain angle
			// that angle is 224
			// if less than 224 degrees, then go full speed
			motorSet(pincer_left, -127);
			pinMode(led_Pincer,OUTPUT);
	//	}
	//	else{
			// otherwise go at a lower speed
			// will help with motor stalling when trying to hold stars and cubes

		//	motorSet(pincer_right, -50);
		//	motorSet(pincer_left, -50);
		//}
	}
		else if (joystickGetDigital(2, 5, JOY_DOWN)){// open claw
					motorSet(pincer_left, 127);
					pinMode(led_Pincer,OUTPUT);
		}
		else if(joystickGetDigital(2,7,JOY_UP)){
			motorSet(pincer_left, -50);
		}
	else {
		motorSet(pincer_left, 0);
		pinMode(led_Pincer,INPUT);
	}
}


// autonomous functions
void driveStop() {
	motorSet(front_left_drive, 0);
	motorSet(front_right_drive, 0);
	motorSet(back_left_drive, 0);
	motorSet(back_right_drive, 0);
}
void liftStop() {
	motorSet(left_lift_Motor1, 0);
	motorSet(left_lift_Motor2, 0);
	motorSet(right_lift_Motor3, 0);
	motorSet(right_lift_Motor4, 0);
}
void pincerStop() {
	motorSet(pincer_left, 0);
}

void driveForward(int encoder_value){
	while((encoderGet(frontLeftEncoder)+ encoderGet(frontRightEncoder))/2 < encoder_value){
		motorSet(front_left_drive,  -127);
		motorSet(front_right_drive,   127);
		motorSet(back_left_drive,   -127);
		motorSet(back_right_drive,   -127);
	}
	driveStop();

}

void driveBackward(int encoder_value){
	while((abs(encoderGet(frontLeftEncoder))+ abs(encoderGet(frontRightEncoder)))/2 < encoder_value){
		motorSet(front_left_drive,  127);
		motorSet(front_right_drive,  - 127);
		motorSet(back_left_drive,   127);
		motorSet(back_right_drive,   127);
	}
	driveStop();
}

void turnRight(int encoder_value){
	while((encoderGet(frontLeftEncoder) +  abs(encoderGet(frontRightEncoder)))/2 < encoder_value){
		motorSet(front_left_drive,  -127);
		motorSet(front_right_drive,  - 127);
		motorSet(back_left_drive,   -127);
		motorSet(back_right_drive,   127);
	}
	driveStop();
}
void turnLeft(int encoder_value){
	while((abs(encoderGet(frontLeftEncoder)) +  encoderGet(frontRightEncoder))/2 < encoder_value){
		motorSet(front_left_drive,  127);
		motorSet(front_right_drive,   127);
		motorSet(back_left_drive,   127);
		motorSet(back_right_drive,  - 127);
	}
	driveStop();
}

void openPincers(int clawPotDesiredValue){
	while (analogRead(pince_pot)>clawPotDesiredValue) {
		motorSet(pincer_left, -127);
	}
	pincerStop();
}
void closePincers(int clawPotDesiredValue){
	while (analogRead(pince_pot)<clawPotDesiredValue) {
		motorSet(pincer_left, 127);
	}
	pincerStop();
}
void liftUp(int liftPotDesiredValue){
	while(analogRead(lift_pot < liftPotDesiredValue)){
		motorSet(left_lift_Motor1, -127);
		motorSet(left_lift_Motor2, -127);
		motorSet(right_lift_Motor3, 127);
		motorSet(right_lift_Motor4, 127);
	}
	liftStop();
}

void liftDown(int liftPotDesiredValue){
	while(analogRead(lift_pot > liftPotDesiredValue)){
		motorSet(left_lift_Motor1, 127);
		motorSet(left_lift_Motor2, 127);
		motorSet(right_lift_Motor3, -127);
		motorSet(right_lift_Motor4, -127);
	}
	liftStop();
}

void driveForwardAndClosePincers(int encoder_value, int clawPotDesiredValue) {
	while(analogRead(pince_pot)<clawPotDesiredValue && (encoderGet(frontLeftEncoder)+ encoderGet(frontRightEncoder))/2 < encoder_value){
		if((encoderGet(frontLeftEncoder)+ encoderGet(frontRightEncoder))/2 < encoder_value) {
			motorSet(front_left_drive,  -127);
			motorSet(front_right_drive,   127);
			motorSet(back_left_drive,   -127);
			motorSet(back_right_drive,   -127);
		}
		else {
			driveStop();
		}

		if (analogRead(pince_pot)<clawPotDesiredValue) {
			motorSet(pincer_left, 127);
		}
		else {
			pincerStop();
		}
	}
	driveStop();
	pincerStop();
}

void autonOne(int flipDrive){
	//Robot starts facing the center cube
	//Preload Star either in front or back
	driveForward(294);
	turnRight(190);
	driveForwardAndClosePincers(424, 1020);
	liftUp(2958);
	turnRight(258);
	driveBackward(-69);
	closePincers(1100);
	liftUp(3520);
	openPincers(2080);
	liftDown(1260);
	turnLeft(-111);
	openPincers(2440);
	driveForward(400);
	closePincers(930);
	driveBackward(-85);
	liftUp(3200);
	openPincers(2080);

}
