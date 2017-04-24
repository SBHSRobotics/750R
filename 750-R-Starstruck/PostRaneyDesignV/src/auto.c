#include "variables.h"
#include "lcd.h"
void autonomous() {// left tile
	if (rightTile > 0){
		right_auton();
	}
	else if (leftTile > 0){
		left_auton();
	}
}
