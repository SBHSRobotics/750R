/*
 * lcd.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Shivam Agrawal
 */
#ifndef LCD_H_
#define LCD_H_
// variables used
#include "variables.h"
#include "functions.h"

int menuCount;
int leftTile;
int rightTile;
int maxNumberMenus;
int subMenuCount;
int menuStay;
int endResultMenu;
int arbitraryVariable ;
int sensorMenuCount ;
int previousSensorLCD;
int sensorMaxNumberMenus;
int batteryMenuCount;
int batteryMaxNumberMenus;
int motorMenuCount;
int motorMaxNumberMenus;

void lcd();
void lcdMotor();
void lcdSensor();
void lcdBattery();
void lcdAutonomous();
void lcdInitiate();
void lcdMainMenu();
void lcdMotorPrint(char string, int motor_port);

#endif /* INCLUDE_LCD_H_ */
