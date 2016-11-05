#include "main.h"


//Motor Ports


//Lift Ports
const unsigned char topleftlift = 2;
const unsigned char bottomleftlift = 3;
const unsigned char toprightlift = 4;
const unsigned char bottomrightlift = 5;


//Pincer Ports
const unsigned char gateLeft = 1;
const unsigned char gateRight = 10;


//X-Drive Ports
const unsigned char backLeft = 6;
const unsigned char frontLeft = 7;
const unsigned char backRight = 8;
const unsigned char frontRight = 9;


//Sensor Ports
const unsigned char pot = 2;


//Program Constants
const int thresh = 15;


//Global Variables
int ch1;
int ch3;
int ch4;
int pos = 0;


void operatorControl() {


	while (1) {


		int up = joystickGetDigital(1, 6, JOY_UP);
		int down = joystickGetDigital(1, 6, JOY_DOWN);
		//buton decleration for lifts


		//Lift Mechanism


		if (up){
			motorSet(topleftlift, 127);
			motorSet(bottomleftlift, 127);
			motorSet(toprightlift, -127);
			motorSet(bottomrightlift, -127);


// if user presses up button, the motors on the left move positive, and the motors on the right move negative(Opposite because the motors are arranged oppositely)


		}
		else if (down){
			motorSet(topleftlift, -127);
			motorSet(bottomleftlift, -127);
			motorSet(toprightlift, 127);
			motorSet(bottomrightlift, 127);


// if user presses down button, the motors on the right move positive, and the motors on the left move negative(Opposite because the motors are arranged oppositely)


		}
		else{
			motorSet(topleftlift, 0);
			motorSet(bottomleftlift, 0);
			motorSet(toprightlift, 0);
			motorSet(bottomrightlift, 0);


// if user doesn’t press a button at all, it doesn’t move at all, hence 0 speed on all motors


		}


		//X-Drive Mechanism


		if (abs(joystickGetAnalog(1, 3)) > thresh){
			ch3 = joystickGetAnalog(1, 3);
		}


		else{
			ch3 = 0;
		}
		if (abs(joystickGetAnalog(1, 4)) > thresh){
			ch4 = joystickGetAnalog(1, 4);
		}
		else{
			ch4 = 0;
		}
		if (abs(joystickGetAnalog(1, 1)) > thresh){
			ch1 = joystickGetAnalog(1, 1);
		}
		else{
			ch1 = 0;
		}
// if user moves joystick, values are set according to where the joystick is on the axis


		//Setting the motors for drive
		motorSet(frontRight, -ch3 + ch4 + ch1);
		motorSet(backRight, -ch3 - ch4 + ch1);
		motorSet(frontLeft, -ch3 - ch4 - ch1);
		motorSet(backLeft, ch3 - ch4 +  ch1);


		//Pincers
		if (joystickGetDigital(1,5,JOY_UP) == 1){
			motorSet(gateLeft, 127);
			motorSet(gateRight, -127);
		}
// If joystick is moved up, gate opens
		else if (joystickGetDigital(1,5,JOY_DOWN) == 1){
			motorSet(gateLeft, -127);
			motorSet(gateRight, 127);
		}
// If joystick is moved down, gate closes


		else{
			motorSet(gateLeft, 0);
			motorSet(gateRight, 0);
		}
// if joystick is still, gate doesn’t move, hence motorset=0


	}


}
