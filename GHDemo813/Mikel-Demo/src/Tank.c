/*
 * Tank.c
 *
 *  Created on: Aug 14, 2016
 *      Author: ascii
 */
#include <main.h>

void stop();

//Auton
void forward(int speed, int time) {
	move(speed, -speed);
	delay(time);
	stop();

}

void turn(int speed, int time) {
	move(speed, -speed);
	delay(time);
	stop();
}

//Teleop
void move(int leftSpeed, int rightSpeed) {
	motorSet(LB, leftSpeed);
	motorSet(LF, leftSpeed);
	motorSet(RF, -rightSpeed);
	motorSet(RB, -rightSpeed);
}

void stop() {
	move(0,0);
}
