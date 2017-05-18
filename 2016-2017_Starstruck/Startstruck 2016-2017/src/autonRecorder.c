#include "variables.h"
#include "functions.h"
#include "lcd.h"
#include "autonRecorder.h"

int maxAuton = 15000;
int intervalTime = 50;
int forLoopRepeat = 300;
struct robotMovements recordedValues[300];
void record() {
		printf("Recording in.........");
	for (int i = 3; i > 0; i --){
			printf("%d, ", i);
			delay(1000);
	}
	for (int i = 0; i < forLoopRepeat; i ++){

	// lift record
if (joystickGetDigital(1,6, JOY_UP)){
			recordedValues[i].lift = 127;
			motorSet(left_lift_Motor1, -127);//  lift goes up
			motorSet(left_lift_Motor2, 127);
			motorSet(right_lift_Motor3, -127);
			motorSet(right_lift_Motor4, 127);
		}
		else if (joystickGetDigital(1,6,JOY_DOWN)){
			recordedValues[i].lift = -127;
			motorSet(left_lift_Motor1, 127);//  lift goes up
			motorSet(left_lift_Motor2, -127);
			motorSet(right_lift_Motor3, 127);
			motorSet(right_lift_Motor4, -127);
		}
		else {
			recordedValues[i].lift = 0;
			motorSet(left_lift_Motor1, 0);//  lift goes up
			motorSet(left_lift_Motor2, 0);
			motorSet(right_lift_Motor3, 0);
			motorSet(right_lift_Motor4, 0);
		}

// drive record
    recordedValues[i].speed = joystickGetAnalog(1, 3);
		recordedValues[i].turn = joystickGetAnalog(1, 1);
		motorSet(front_left_drive, joystickGetAnalog(1,3) + joystickGetAnalog(1,1) );
		motorSet(front_right_drive,   -joystickGetAnalog(1,3) + joystickGetAnalog(1,1) );
		motorSet(back_left_drive,  joystickGetAnalog(1,3) + joystickGetAnalog(1,1) );
		motorSet(back_right_drive,   -joystickGetAnalog(1,3) + joystickGetAnalog(1,1) );

		// pincer record
		if (joystickGetDigital(1,5, JOY_UP)){
			recordedValues[i].pincer = 127;
			motorSet(pincer_right, -127);
			motorSet(pincer_left, -127);

		}
		else if (joystickGetDigital(1,5,JOY_DOWN)){
			recordedValues[i].pincer = -127;
			motorSet(pincer_right, 127);
			motorSet(pincer_left, 127);

		}
		else {
			recordedValues[i].pincer = 0;
			motorSet(pincer_right, 0);
			motorSet(pincer_left, 0);

		}


		delay(intervalTime);
}
}

void save(FILE* file_var, char* filename){
  file_var = fopen(filename, "w");
  fwrite(recordedValues, 1, forLoopRepeat, file_var);
	if (file_var== NULL){
		printf("Error saving Autonomous\n");
	}
	else{
		printf("Save Successful\n");
	}
  fclose(file_var);
}
void playback(FILE* file_var, char* filename) {
	file_var = fopen(filename, "r");
	if (file_var == NULL){
		printf("Error playing back the function\n");
	}
	else{
		printf("playback successful\n");
	}
	fread(recordedValues, 1, forLoopRepeat, file_var);
	fclose(file_var);
	for (int i = 0; i < forLoopRepeat; i ++){
		printf("MOMENT  %d\n", i);
		printf("lift: %d\n", recordedValues[i].lift);
		printf("drive: %d\n", recordedValues[i].speed);
		printf("turn: %d\n", recordedValues[i].lift);
		printf("pincer: %d\n\n", recordedValues[i].lift);
		moveLift(recordedValues[i].lift);
    moveDrive(recordedValues[i].speed);
    turnDrive(recordedValues[i].turn);
    movePincers(recordedValues[i].pincer);
    delay(50);
  }
}
void moveLift(int right_speed){
	if (right_speed > 0){
		motorSet(left_lift_Motor1, -right_speed);
		motorSet(left_lift_Motor2, right_speed);
		motorSet(right_lift_Motor3, -right_speed);
		motorSet(right_lift_Motor4, right_speed);
}
else if (right_speed < 0){
		motorSet(left_lift_Motor1, right_speed);
		motorSet(left_lift_Motor2, -right_speed);
		motorSet(right_lift_Motor3, right_speed);
		motorSet(right_lift_Motor4, -right_speed);
}
else {
		motorSet(left_lift_Motor1, 0);
		motorSet(left_lift_Motor2, 0);
		motorSet(right_lift_Motor3, 0);
		motorSet(right_lift_Motor4, 0);
}
}
void moveDrive(int joystick_value){
	if (joystick_value > 0){
		motorSet(front_left_drive, joystick_value);
		motorSet(front_right_drive, -joystick_value);
		motorSet(back_left_drive, joystick_value);
		motorSet(back_right_drive, -joystick_value);
	}
	else if (joystick_value < 0){
		motorSet(front_left_drive, -joystick_value);
		motorSet(front_right_drive, joystick_value);
		motorSet(back_left_drive, -joystick_value);
		motorSet(back_right_drive, joystick_value);
	}
	else{
		motorSet(front_left_drive, 0);
		motorSet(front_right_drive, 0);
		motorSet(back_left_drive, 0);
		motorSet(back_right_drive, 0);
}

}
void turnDrive(int joystick_value){
	if (joystick_value > 0){
		motorSet(front_left_drive, joystick_value);
		motorSet(front_right_drive, joystick_value);
		motorSet(back_left_drive, joystick_value);
		motorSet(back_right_drive, joystick_value);
	}
	else if (joystick_value < 0){
		motorSet(front_left_drive, -joystick_value);
		motorSet(front_right_drive, -joystick_value);
		motorSet(back_left_drive, -joystick_value);
		motorSet(back_right_drive, -joystick_value);
	}
	else{
		motorSet(front_left_drive, 0);
		motorSet(front_right_drive, 0);
		motorSet(back_left_drive, 0);
		motorSet(back_right_drive, 0);
}
}
void movePincers(int right_speed){
	if (right_speed > 0){
		motorSet(pincer_right, -right_speed);
		motorSet(pincer_left, -right_speed);
}
else if (right_speed < 0){
		motorSet(pincer_right, right_speed);
		motorSet(pincer_left, right_speed);
}
else {
		motorSet(pincer_right, 0);
		motorSet(pincer_left, 0);
}
}
