/*
 * lcd.c
 *
 *  Created on: Feb 15, 2017
 *      Author: Shivam Agrawal
 */
/*Author: Shivam Agrawal
*/

#include "functions.h"
#include "variables.h"
#include "lcd.h"
//#include "autonRecorder.h"

int previousLCD = 0;
int menuCount = 0;
int leftTile = 0;
int rightTile = 0;;
int maxNumberMenus = 5;
int subMenuCount = 0;
int menuStay = 0;
int endResultMenu = 0;
int endResult_Menu_Inner = 0;
int arbitraryVariable = 0;
int sensorMenuCount = 0;
int previousSensorLCD = 0;
int sensorArbValue = 0;
int sensorMaxNumberMenus = 2;
int sensorSubMenuCount = 0;
int numbOfEncod = 2;
int sensorMenuStay = 0;
int batteryMenuCount = 0;
int batteryMaxNumberMenus = 1;
int motorMenuCount = 0;
int motorMaxNumberMenus = 9;
int autonRecorderMenuCount = 0;
//int autonRecorderMaxNumberMenus = 1;
//int arbitraryValueTwo = 0;
// Strings
char left_lift_Motor1LCD[17];
char left_lift_Motor2LCD[17];
char right_lift_Motor3LCD[17];
char right_lift_Motor4LCD[17];
char front_left_driveLCD[17];
char front_right_driveLCD[17];
char back_left_driveLCD[17];
char back_right_driveLCD[17];
char pincer_leftLCD[17];
char pincer_rightLCD[17];
char battery[17];
char backupBattery[17];
char encoderAve[17];
char liftPotLCD[17];
char pincePotLCD[17];
// main lcd function
void lcd(){
  lcdMainMenu();
	// sub menu
	switch(subMenuCount){
		case 0:
		break;
		case 1:// auton choice
	    lcdAutonomous();
		break;
		case 2:// battery choice
      lcdBattery();
		break;
		case 3:// sensor choice
      lcdSensor();
		break;
		case 4:// motor choice
      lcdMotor();
    break;
  //  case 5:
  //    lcdAutonRecorder();
  //  break;
	}
	previousLCD = lcdReadButtons(uart1);
}
/*void lcdAutonRecorder(){
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    lcdClear(uart1);
    menuStay == LCD_BTN_CENTER;
    arbitraryVariable = 1;
    lcdSetText(uart1, 1, "CONFIRM");
    if (((lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD == LCD_BTN_RIGHT) || endResultMenu == LCD_BTN_RIGHT) && arbitraryValueTwo = 0){
      for (int j = 1; j < 4; j ++){
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Recording in...");
        lcdSetText(uart1, 2, j);
      }
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Recording");
      record();
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Finished");
      delay(1000);
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Save?");
      lcdSetText(uart1, 2, "No     Yes");
      if((lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD == LCD_BTN_RIGHT) || endResult_Menu_Inner == LCD_BTN_RIGHT){
        endResult_Menu_Inner = LCD_BTN_RIGHT;
        arbitraryValueTwo = 1;
        if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD != LCD_BTN_LEFT){// if clicked now, and not clicked 100 ms before
          autonRecorderMenuCount--;
        }
        else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD != LCD_BTN_RIGHT){
          autonRecorderMenuCount++;
        }
        if (autonRecorderMenuCount < 0){
          autonRecorderMenuCount = autonRecorderMaxNumberMenus;
        }
        else if (autonRecorderMenuCount > autonRecorderMaxNumberMenus){
          autonRecorderMenuCount = 0;
        }
        switch(autonRecorderMenuCount){
          case 0:
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Auton Left");
            if(lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
              saveAuton(Auton_one, "Auton_1");
              menuCount = 0;
              menuStay = 0;
              arbitraryVariable = 0;
              endResultMenu = 0;
              endResult_Menu_Inner = 0;
              arbitraryValueTwo = 0;
            }
            break;
          case 1:
            lcdClear(uart1);
            lcdSetText(uart1, 1, "Auton Right");
            if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
              saveAuton(Auton_two, "Auton_2");
              menuCount = 0;
              menuStay = 0;
              arbitraryVariable = 0;
              endResultMenu = 0;
              endResult_Menu_Inner = 0;
              arbitraryValueTwo = 0;
            }
            break;
        }
      }
      else if((lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD == LCD_BTN_LEFT) && arbitraryValueTwo = 0){
        menuCount = 0;
        menuStay = 0;
        arbitraryVariable = 0;
        endResultMenu = 0;
      }
    }
    else if ((lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD == LCD_BTN_LEFT)){
      menuCount = 0;
      menuStay = 0;
      arbitraryVariable = 0;
      endResultMenu = 0;
    }
  }
}
*/
void lcdMotor(){// code for the motor sub menu and displays
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    lcdClear(uart1);
    arbitraryVariable = 1;
    menuStay = LCD_BTN_CENTER;
    // motor menu!!
    if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD != LCD_BTN_LEFT){// if clicked now, and not clicked 100 ms before
      motorMenuCount--;
    }
    else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD != LCD_BTN_RIGHT){
      motorMenuCount++;
    }
    if (motorMenuCount < 0){
      motorMenuCount = motorMaxNumberMenus;
    }
    else if (motorMenuCount > motorMaxNumberMenus){
      motorMenuCount = 0;
    }
    switch(motorMenuCount){
      case 0:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Top Left Drive");
        snprintf(front_left_driveLCD, 17, "%d", (motorGet(front_left_drive)));
        lcdSetText(uart1, 2, front_left_driveLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 1:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Top Right Drive");
        snprintf(front_right_driveLCD, 17, "%d", (motorGet(front_right_drive)));
        lcdSetText(uart1, 2, front_right_driveLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 2:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Back Left Drive");
        snprintf(back_left_driveLCD, 17, "%d", (motorGet(back_left_drive)));
        lcdSetText(uart1, 2, back_left_driveLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 3:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Back Right Drive");
        snprintf(back_right_driveLCD, 17, "%d", (motorGet(back_right_drive)));
        lcdSetText(uart1, 2, back_right_driveLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 4:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift 1");
        snprintf(left_lift_Motor1LCD, 17, "%d", (motorGet(left_lift_Motor1)));
        lcdSetText(uart1, 2, left_lift_Motor1LCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 5:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift 2");
        snprintf(left_lift_Motor2LCD, 17, "%d", (motorGet(left_lift_Motor2)));
        lcdSetText(uart1, 2, left_lift_Motor2LCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 6:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift 3");
        snprintf(right_lift_Motor3LCD, 17, "%d", (motorGet(right_lift_Motor3)));
        lcdSetText(uart1, 2, right_lift_Motor3LCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 7:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift 4");
        snprintf(right_lift_Motor4LCD, 17, "%d", (motorGet(right_lift_Motor4)));
        lcdSetText(uart1, 2, right_lift_Motor4LCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 8:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Pincer Left");
      snprintf(pincer_leftLCD, 17, "%d", (motorGet(pincer_left)));
      lcdSetText(uart1, 2, pincer_leftLCD);
      if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
        menuCount = 0;
        menuStay = 0;
        arbitraryVariable = 0;
        endResultMenu = 0;
      }
      break;
      case 9:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Pincer Right");
      snprintf(pincer_rightLCD, 17, "%d", (motorGet(pincer_right)));
      lcdSetText(uart1, 2, pincer_rightLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
    }
  }
}
void lcdSensor(){// code for the sensor sub menu and displays in the lcd
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    lcdClear(uart1);
    arbitraryVariable = 1;
    menuStay = LCD_BTN_CENTER;
    // sensor menu!!
    if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD != LCD_BTN_LEFT){// if clicked now, and not clicked 100 ms before
      sensorMenuCount--;
    }
    else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD != LCD_BTN_RIGHT){
      sensorMenuCount++;
    }
    if (sensorMenuCount < 0){
      sensorMenuCount = sensorMaxNumberMenus;
    }
    else if (sensorMenuCount > sensorMaxNumberMenus){
      sensorMenuCount = 0;
    }
    switch (sensorMenuCount) {
      case 0:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Encoder Average:");
        snprintf(encoderAve, 17, "%d", ((encoderGet(frontLeftEncoder) + encoderGet(frontRightEncoder) +encoderGet(backLeftEncoder) +encoderGet(backRightEncoder))/numbOfEncod));
        lcdSetText(uart1, 2, encoderAve);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 1:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift Pot:");
        snprintf(liftPotLCD, 17, "%d", (analogRead(lift_pot)));
        lcdSetText(uart1, 2, liftPotLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
      case 2:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Pincer Pot Ave:");
        snprintf(pincePotLCD, 17, "%d", (analogRead(pince_pot_left) + analogRead(pince_pot_right))/2);
        lcdSetText(uart1, 2, pincePotLCD);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
          endResultMenu = 0;
        }
      break;
    }
  }
}

void lcdBattery(){// code for the battery sub display in lcd
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    arbitraryVariable = 1;
    menuStay = LCD_BTN_CENTER;

    // battery menu!!
    if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD != LCD_BTN_LEFT){// if clicked now, and not clicked 100 ms before
      batteryMenuCount--;
    }
    else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD != LCD_BTN_RIGHT){
      batteryMenuCount++;
    }
    if (batteryMenuCount < 0){
      batteryMenuCount = batteryMaxNumberMenus;
    }
    else if (batteryMenuCount > batteryMaxNumberMenus){
      batteryMenuCount = 0;
    }

    switch(batteryMenuCount){
      case 0:
        snprintf(battery, 17, "Battery: %f", ((double)powerLevelMain()/1000));
        lcdClear(uart1);
        lcdSetText(uart1, 1, battery);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
        }
      break;
      case 1:
        snprintf(backupBattery, 17, "%f", ((double)powerLevelBackup()/1000));// prints extra battery for spacing issues on the lcd
        lcdSetText(uart1, 1, "Backup Battery:");
        lcdSetText(uart1, 2, backupBattery);
        if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
          menuCount = 0;
          menuStay = 0;
          arbitraryVariable = 0;
        }
      break;
    }
  }
}
void lcdAutonomous(){// code for the autonomous sub menu in the lcd
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    arbitraryVariable = 1;
    lcdClear(uart1);// printing the options
    lcdSetText(uart1, 1, "Left Tile");
    lcdSetText(uart1, 2, "Right Tile");
    menuStay = LCD_BTN_CENTER;
    // if you press the left button, the left auton will be selected
    if ((lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD == LCD_BTN_LEFT) || endResultMenu == LCD_BTN_LEFT){
      lcdClear(uart1);// printing the options
      lcdSetText(uart1, 1, "Left is selected");
      leftTile++;
      endResultMenu = LCD_BTN_LEFT;
      if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
        menuCount = 0;
        menuStay = 0;
        endResultMenu = 0;
        arbitraryVariable = 0;
      }
    }
      // if you press the right button, the right auton will be selected
    else if ((lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD == LCD_BTN_RIGHT) || endResultMenu == LCD_BTN_RIGHT){
      lcdClear(uart1);// printing the options
      lcdSetText(uart1, 1, "Right is");
      lcdSetText(uart1, 2, "selected");
      rightTile++;
      endResultMenu = LCD_BTN_RIGHT;
      if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
        menuCount = 0;
        menuStay = 0;
        endResultMenu = 0;
        arbitraryVariable = 0;
      }
    }
    if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
      menuCount = 0;
      menuStay = 0;
      arbitraryVariable = 0;
    }
  }
}
void lcdMainMenu(){// code for main menu in the lcd
  if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousLCD != LCD_BTN_LEFT && arbitraryVariable == 0){// if clicked now, and not clicked 20 ms before
    menuCount--;
  }
  else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD != LCD_BTN_RIGHT && arbitraryVariable == 0){
    menuCount++;
  }
  if (menuCount < 0){
    menuCount = maxNumberMenus;
  }
  else if (menuCount > maxNumberMenus){
    menuCount = 0;
  }
  // Main Menu
  switch(menuCount){
    case 0:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "750R's LCD");
      lcdSetText(uart1, 2 , "Welcome");
      subMenuCount = 0;
      break;
    case 1:
      lcdClear(uart1);
      lcdSetText(uart1, 1 , "Autonomous");
      subMenuCount = 1;
      break;
    case 2:
      lcdClear(uart1);
      lcdSetText(uart1, 1 , "Battery");
      subMenuCount = 2;
      break;
    case 3:
      lcdClear(uart1);
      lcdSetText(uart1, 1 , "Sensors");
      subMenuCount = 3;
      break;
    case 4:
      lcdClear(uart1);
      lcdSetText(uart1, 1 , "Motors");
      subMenuCount = 4;
      break;
    case 5:
      lcdClear(uart1);
      lcdSetText(uart1, 1, "Auton Recorder");
      subMenuCount = 5;
  }
}

void lcdInitiate(){// must be done in opcontrol, before while loop
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);
}


