/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

 #include "variables.h"
 #include "functions.h"
 #include "lcd.h"
 #include "autonRecorder.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
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
  	while( abs(encoderGet(frontLeftEncoder)) < encoder_value ) {
  		motorSet(front_left_drive,  127);
  		motorSet(front_right_drive,   -127);
  		motorSet(back_left_drive,   127);
  		motorSet(back_right_drive,   -127);

  	}
  	driveStop();

  }
  void driveBackward(int encoder_value){
  	while( abs(encoderGet(frontLeftEncoder)) > encoder_value ) {
  		motorSet(front_left_drive,  -127);
  		motorSet(front_right_drive,   127);
  		motorSet(back_left_drive,   -127);
  		motorSet(back_right_drive,   127);
  	}
  	driveStop();
  }

  void turnRight(int encoder_value){
  	while( abs(encoderGet(frontLeftEncoder)) < encoder_value ) {
  		motorSet(front_left_drive,  127);
  		motorSet(front_right_drive,   127);
  		motorSet(back_left_drive,   127);
  		motorSet(back_right_drive,   127);
  	}
  	driveStop();
  }
  void turnLeft(int encoder_value){
  	while( abs(encoderGet(frontLeftEncoder)) < encoder_value ) {
  		motorSet(front_left_drive,  -127);
  		motorSet(front_right_drive,   -127);
  		motorSet(back_left_drive,   -127);
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
      motorSet(left_lift_Motor1, -127);//  lift goes up
  		motorSet(left_lift_Motor2, 127);
  		motorSet(right_lift_Motor3, -127);
  		motorSet(right_lift_Motor4, 127);
  	}
  	liftStop();
  }

  void liftDown(int liftPotDesiredValue){
  	while(analogRead(lift_pot > liftPotDesiredValue)){
      motorSet(left_lift_Motor1, 127);
  		motorSet(left_lift_Motor2, -127);
  		motorSet(right_lift_Motor3, 127);
  		motorSet(right_lift_Motor4, -127);
  	}
  	liftStop();
  }

void autonOne(int flipDrive){
  	//Robot starts facing the center cube
  	//Preload Star either in front or back
  	driveForward(294);
  	turnRight(190);
  	driveForward(424);
    closePincers(1020);
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
/*  if (leftTile == 1){
    //playback(Auton_one, "Auton_1");
  }
  else if(rightTile == 1){
  //  playback(Auton_two, "Auton_2");
  }
  else if (progSkills == 1){
    */
    //playback(Auton_one, "Auton_1");
    /*if (leftTile == 1){
      flipTurns = 1;
      autonOne(flipTurns);
    }
    else if(rightTile == 1){
      flipTurns = -1;
      autonOne(flipTurns);
    }
    else if(progSkills == 1){

    }
    else {
      autonOne(1);
    }*/
    //autonOne(1);
      /*motorSet(pincer_left, 127);
      driveForward(294);
      turnRight(190);
      driveForward(424);
      closePincers(1020);
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
  	openPincers(2080);*/

    /*
    //drive forward
    motorSet(front_left_drive,  127);
    motorSet(front_right_drive,   -127);
    motorSet(back_left_drive,   127);
    motorSet(back_right_drive,   -127);
    delay(800);
    motorStopAll();
//turn right
    motorSet(front_left_drive,  127);
    motorSet(front_right_drive,   127);
    motorSet(back_left_drive,   127);
    motorSet(back_right_drive,   127);
    delay(400);
    motorStopAll();
//drive forward to cube
    motorSet(front_left_drive,  127);
    motorSet(front_right_drive,   -127);
    motorSet(back_left_drive,   127);
    motorSet(back_right_drive,   -127);
    delay(800);
    motorStopAll();
//close pincers
    motorSet(pincer_left, 127);
    delay(1000);
    motorStopAll();
//lift up
    motorSet(left_lift_Motor1, -127);//  lift goes up
    motorSet(left_lift_Motor2, 127);
    motorSet(right_lift_Motor3, -127);
    motorSet(right_lift_Motor4, 127);
    delay(300);
    motorStopAll();
//turn right
    motorSet(front_left_drive,  127);
    motorSet(front_right_drive,   127);
    motorSet(back_left_drive,   127);
    motorSet(back_right_drive,   127);
    delay(300);
    motorStopAll();
    //drive backward
    motorSet(front_left_drive,  -127);
    motorSet(front_right_drive,   127);
    motorSet(back_left_drive,   -127);
    motorSet(back_right_drive,   127);
    delay(300);
    motorStopAll();
//lift cube up
    motorSet(left_lift_Motor1, -127);//  lift goes up
    motorSet(left_lift_Motor2, 127);
    motorSet(right_lift_Motor3, -127);
    motorSet(right_lift_Motor4, 127);
    delay(600);
//open pincers`
    motorSet(pincer_left, 127);
    delay(300);
    motorStopAll();

//lift down
motorSet(left_lift_Motor1, 127);
motorSet(left_lift_Motor2, -127);
motorSet(right_lift_Motor3, 127);
motorSet(right_lift_Motor4, -127);
delay(600);
motorStopAll();


    // drive forward to stars
    motorSet(front_left_drive,  127);
    motorSet(front_right_drive,   127);
    motorSet(back_left_drive,   127);
    motorSet(back_right_drive,   127);
    delay(700);
    motorStopAll();

    //close pincers`
        motorSet(pincer_left, -127);
        delay(300);
        motorStopAll();

//lift up
    motorSet(left_lift_Motor1, -127);//  lift goes up
    motorSet(left_lift_Motor2, 127);
    motorSet(right_lift_Motor3, -127);
    motorSet(right_lift_Motor4, 127);
    delay(300);
    motorStopAll();

    motorSet(pincer_left, 127);
    delay(300);
    motorStopAll();

    //drive backward
    motorSet(front_left_drive,  -127);
    motorSet(front_right_drive,   127);
    motorSet(back_left_drive,   -127);
    motorSet(back_right_drive,   127);
    delay(700);
    motorStopAll();

    //lift up
        motorSet(left_lift_Motor1, -127);//  lift goes up
        motorSet(left_lift_Motor2, 127);
        motorSet(right_lift_Motor3, -127);
        motorSet(right_lift_Motor4, 127);
        delay(700);
        motorStopAll();

        //open pincers`
            motorSet(pincer_left, 127);
            delay(300);
            motorStopAll();
*/











  }
