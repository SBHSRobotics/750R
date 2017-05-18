#ifndef AUTONRECORDER_H_
#define AUTONRECORDER_H_
#include "main.h"

int maxAuton;
int intervalTime;
char file_save_to[17];
FILE *Auton_one;// make a file called auton_1
FILE *Auton_two;// make a file called auton_2
FILE *Prog_Skills;
struct robotMovements {

	signed char speed;
	signed char lift;
	signed char turn;
	signed char pincer;

};
void record();
void save(FILE* file_var, char* filename);
void playback(FILE* file_var, char* filename);
void moveLift(int right_speed);
void moveDrive(int joystick_value);
void turnDrive(int joystick_value);
void movePincers(int right_speed);

#endif
