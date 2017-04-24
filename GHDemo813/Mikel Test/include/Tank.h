/*
 * Tank.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Admin
 */

#ifndef INCLUDE_TANK_H_
#define INCLUDE_TANK_H_


//motor ports

const static int LF=3;
const static int RF=4;
const static int LB=5;
const static int RB=6;

//Auton
void forward(int speed, int time);

void turn(int speed, int time);

//Teleop
void move(int leftSpeed, int rightSpeed);


#endif /* INCLUDE_TANK_H_ */
