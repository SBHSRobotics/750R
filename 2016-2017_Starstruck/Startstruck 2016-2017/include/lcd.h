#ifndef LCD_H_
#define LCD_H_
// variables used
#include "variables.h"
#include "functions.h"

int menuCount;
int leftTile;
int rightTile;
int progSkills;
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
int autonRecorderMenuCount;
int autonRecorderMaxNumberMenus;
int arbitraryValueTwo;

void lcd();
void lcdMotor();
void lcdSensor();
void lcdBattery();
void lcdAutonomous();
void lcdInitiate();
void lcdMainMenu();
void lcdMotorPrint(char string, int motor_port);
void lcdProgrammingSkills();
void lcdAutonRecorder();
#endif
