#include "PIDHolonomic.h"
#include "main.h"
float Kp = 1.0;
float Ki = .5;
float Kd = .75;
int IME_1 = 0;
int IME_2 = 0;
int IME_3 = 0;
int IME_4 = 0;
int drive_motor_fl = 1;
int drive_motor_fr = 2;
int drive_motor_br = 3;
int drive_motor_bl = 4;
struct PIDValues{
  int error;
  int errorTotal;
  int lastError;
  float derivative;
  float integral;
  float proportional;
  char speed[10];
};
struct PIDValues frontLeft;
struct PIDValues frontRight;
struct PIDValues backRight;
struct PIDValues backLeft;

int PID(int desired_value, int ime_address, int ime, float derivative, float integral, float proportional, int error, int lastError, int errorTotal){
  imeGet(ime_address, &ime);
  error = desired_value - ime;
  derivative = (lastError - error) * Kd;
  proportional = error * Kp;
  // anti wind up code; the purpose of the integral term is to change the output of the motors
  //when the deriative and the proportional get too small to do it, but if not controlled can get very big
  //I put this set of ifs in order to let the errorTotal start to accumulate only when I need to
  if (error > 6){
    errorTotal = 0;
  }
  else{
    errorTotal += error;
  }
  integral = errorTotal * Ki;
  lastError = error;
  return derivative + proportional + integral;
}
int getAxes(int channel){
  if (joystickGetAnalog(1,channel) > 5){
    return channel;
  }
  return 0;
}
void drive(int x, int y, int z){
  // we need the max value to be less than 127.If it isnt, the pid loop will only work for when the motor is
  // going above the desired value. That is usually not the case, so it has to be less in order to account
  // for that
  if (x > 115){
    x = 115;
  }
  else if(y > 115){
    y = 115;
  }
  else if (z > 115){
    z = 115;
  }
  // I created four different pid loops, one for each wheel. PIDs should be in loops, but this is fine because it uses the outside loop in operator control
  // also, the cortex's speed will make the difference between putting a loop here and using the one in opcontrol like half a millisecond
  // if the loop is here, there will be an infinite loop
  motorSet(drive_motor_fl, PID(y + x + z, 0, IME_1, frontLeft.derivative, frontLeft.integral,frontLeft.proportional,frontLeft.error,frontLeft.lastError, frontLeft.errorTotal));
  motorSet(drive_motor_fr, PID(-y + x + z, 1, IME_2, frontRight.derivative, frontRight.integral, frontRight.proportional, frontRight.error, frontRight.lastError, frontRight.errorTotal));
  motorSet(drive_motor_br, PID(-y - x + z, 2, IME_3, backRight.derivative, backRight.integral, backRight.proportional, backRight.error, backRight.lastError, backRight.errorTotal));
  motorSet(drive_motor_bl, PID(y - x + z, IME_ADDR_MAX, IME_4, backLeft.derivative, backLeft.integral, backLeft.proportional, backLeft.error, backLeft.lastError, backLeft.errorTotal));
  // first motor is front left, and is the first IME
  // second motor is front right, and is the second IME
  // third motor is back right, and is the third IME
  // last motor is the back left, and is the fourth and max IME
}
void printSpeed(){
  imeGet(0, &IME_1);
  imeGet(2, &IME_2);
  imeGet(2, &IME_3);
  imeGet(IME_ADDR_MAX, &IME_4);
  snprintf(frontLeft.speed, 5, "%d", IME_1);
  snprintf(frontRight.speed, 5, "%d", IME_2);
  snprintf(backRight.speed, 5, "%d", IME_3);
  snprintf(backLeft.speed, 5, "%d", IME_4);
  printf(frontLeft.speed);
  printf(frontRight.speed);
  printf(backRight.speed);
  printf(backLeft.speed);
}
