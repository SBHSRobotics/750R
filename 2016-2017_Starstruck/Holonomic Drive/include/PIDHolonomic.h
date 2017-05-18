#ifndef PIDHOLONOMIC_H
#define PIDHOLONOMIC_H

int PID(int desired_value);
int getAxes(int channel);
void drive(int x, int y, int z);
void printSpeed();
#endif
