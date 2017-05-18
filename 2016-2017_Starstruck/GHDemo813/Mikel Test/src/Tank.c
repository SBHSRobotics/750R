/*
 * Tank.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Admin
 */
#include <main.h>
void stop();
//Auton
void forward(int speed, int time){
	move(speed, -speed);
	delay(time);
}

void turn(int speed, int time){
	move(speed, -speed);
	delay(time);
}

//Teleop
void move(int leftSpeed, int rightSpeed){
	motorSet(LB, leftSpeed);
	motorSet(LF, leftSpeed);
	motorSet(RB, -rightSpeed);
	motorSet(RF, -rightSpeed);
}

void stop(){
	move(0,0);
}



