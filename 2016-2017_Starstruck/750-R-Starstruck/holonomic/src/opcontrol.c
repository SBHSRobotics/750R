/**
 * File for operator control code.
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 ********************************************************************************/

#include "main.h"

/**
 * Runs the user operator control code.
 *
 * This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If the robot is disabled or communications is lost, the operator control task will be stopped by the kernel. Re-enabling the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will run the operator control task. Be warned that this will also occur if the VEX Cortex is tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

//Motor Ports
const unsigned char topleftlift = 3;
const unsigned char bottomleftlift = 4;
const unsigned char toprightlift = 8;
const unsigned char bottomrightlift = 9;
//(Lift Port Definitions)



const unsigned char backLeft = 5;
const unsigned char frontLeft = 6;
const unsigned char backRight = 7;
const unsigned char frontRight = 2;
//(X-Drive Port Definitions)



const unsigned char pincerleft = 1;
const unsigned char pincerright = 10;
//(Pincers Port Defenitions)


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

		int up = joystickGetDigital(1, 8, JOY_UP);
		int down = joystickGetDigital(1, 8, JOY_DOWN);
		//Lift Mechanism
		if (up) {
			motorSet(topleftlift, 127);
			motorSet(bottomleftlift, 127);
			motorSet(toprightlift, -127);
			motorSet(bottomrightlift, -127);
		} else if (down) {
			motorSet(topleftlift, -127);
			motorSet(bottomleftlift, -127);
			motorSet(toprightlift, 127);
			motorSet(bottomrightlift, 127);
		} else {
			motorSet(topleftlift, 0);
			motorSet(bottomleftlift, 0);
			motorSet(toprightlift, 0);
			motorSet(bottomrightlift, 0);
		}
		//X-Drive Mechanism
		if (abs(joystickGetAnalog(1, 3)) > thresh) {
			ch3 = joystickGetAnalog(1, 3);
		} else {
			ch3 = 0;
		}
		if (abs(joystickGetAnalog(1, 4)) > thresh) {
			ch4 = joystickGetAnalog(1, 4);
		} else {
			ch4 = 0;
		}
		if (abs(joystickGetAnalog(1, 1)) > thresh) {
			ch1 = joystickGetAnalog(1, 1);
		} else {
			ch1 = 0;
		}

		//Pincer Mechanism
		int open=joystickGetDigital(1, 8, JOY_LEFT);
		int close=joystickGetDigital(1, 8, JOY_RIGHT);

		if(open){
			motorSet(pincerright, -127);
			motorSet(pincerleft, 127);
		}

		else if(close){
			motorSet(pincerright, 127);
			motorSet(pincerleft, -127);
		}

		//Setting the motors
		motorSet(frontRight, -ch3 + ch4 + ch1);
		motorSet(backRight, ch3 + ch4 - ch1);
		motorSet(frontLeft, -ch3 - ch4 - ch1);
		motorSet(backLeft, -ch3 + ch4 - ch1);

	}
}
