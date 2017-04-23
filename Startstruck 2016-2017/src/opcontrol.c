/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "functions.h"
#include "variables.h"
#include "lcd.h"
#include "autonRecorder.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
 int ch1 = 0;
 int ch3 = 0;
int x = 0;
 void operatorControl() {
  lcdInitiate();
 	while (true){
 		ch3 = joystickAxes(3);
 		ch1 = joystickAxes(1);
 		drive(ch3, ch1);
 		// lift code
 		lift();
 		// pincer code
 		pincers();
    lcd();
 		delay(100);
    if(joystickGetDigital(2,7,JOY_DOWN)){
      motorSet(left_lift_Motor1, -127);
      delay(2000);
      motorSet(left_lift_Motor1, 0);
      motorSet(left_lift_Motor2, 127);
      delay(2000);
      motorSet(left_lift_Motor2, 0);
      motorSet(right_lift_Motor3, -127);
      delay(2000);
      motorSet(right_lift_Motor3, 0);
      motorSet(right_lift_Motor4, 127);
      delay(2000);
      motorSet(right_lift_Motor4, 0);
    }
 	}
 }
