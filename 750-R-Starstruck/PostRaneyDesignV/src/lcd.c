/*Author: Shivam Agrawal
*/

#include "main.h"
#include "variables.h"
#include "lcd.h"

int previousLCD = 0;
int menuCount = 0;
int leftTile = 0;
int rightTile = 0;;
const int maxNumberMenus = 4;
int subMenuCount = 0;
int menuStay = 0;
int endResultMenu = 0;
int arbitraryVariable = 0;
char battery[17];
char backupBattery[17];
char encoderAve[17];
char liftPotLCD[17];
char pincePotLCD[17];
int sensorMenuCount = 0;
int previousSensorLCD = 0;
int sensorArbValue = 0;
int sensorMaxNumberMenus = 2;
int sensorSubMenuCount = 0;
int numbOfEncod = 2;
int sensorMenuStay = 0;
void lcdMotor(){// code for the motor sub menu and displays

}
void lcdSensor(){// code for the sensor sub menu and displays in the lcd
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    lcdClear(uart1);
    arbitraryVariable = 1;
    menuStay = LCD_BTN_CENTER;
    // sensor menu!!
    if (lcdReadButtons(uart1) == LCD_BTN_LEFT && previousSensorLCD != LCD_BTN_LEFT && sensorArbValue == 0){// if clicked now, and not clicked 20 ms before
      sensorMenuCount--;
    }
    else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousSensorLCD != LCD_BTN_RIGHT && sensorArbValue == 0){
      sensorMenuCount++;
    }
    if (sensorMenuCount < 0){
      sensorMenuCount = sensorMaxNumberMenus;
    }
    else if (sensorMenuCount > sensorMaxNumberMenus){
      sensorMenuCount = 0;
    }
    switch (sensorMenuCount) {
      case 0:// if you press middle button, should print encoder ave
            // if
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Encoder Average");
        sensorSubMenuCount
/*        if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER) || endResultMenu == LCD_BTN_CENTER){
          sensorArbValue = 1;
          endResultMenu = LCD_BTN_CENTER;
          lcdClear(uart1);
          lcdSetText(uart1, 1, "Encoder Ave");
          snprintf(encoderAve,17,"%d", (encoderGet(frontLeftEncoder) +encoderGet(frontRightEncoder) +encoderGet(backLeftEncoder) +encoderGet(backRightEncoder) )/numbOfEncod);
          lcdSetText(uart1, 2, encoderAve);
          if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousSensorLCD != LCD_BTN_CENTER){// going back in the menu
            menuCount = 0;
            menuStay = 0;
            arbitraryVariable = 0;
            endResultMenu = 0;
          }
        }
        */
      break;
      case 1:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Lift Pot");
        sensorSubMenuCount = 1;
      break;
      case 2:
        lcdClear(uart1);
        lcdSetText(uart1, 1, "Pincer Pot");
        sensorSubMenuCount = 2;
      break;
    }
    previousSensorLCD = lcdReadButtons(uart1);
  }

}

void lcdBattery(){// code for the battery sub display in lcd
  if ((lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD == LCD_BTN_CENTER) || menuStay == LCD_BTN_CENTER){
    arbitraryVariable = 1;
    menuStay = LCD_BTN_CENTER;
    snprintf(battery, 17, "Battery: %f", ((double)powerLevelMain()/1000));
    lcdClear(uart1);
    lcdSetText(uart1, 1, battery);
    if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
      menuCount = 0;
      menuStay = 0;
      arbitraryVariable = 0;
    }
    if ((lcdReadButtons(uart1) == LCD_BTN_RIGHT && previousLCD == LCD_BTN_RIGHT) || endResultMenu == LCD_BTN_RIGHT){
      snprintf(backupBattery, 17, "%f", ((double)powerLevelBackup()/1000));// prints extra battery for spacing issues on the lcd
      lcdSetText(uart1, 1, "Backup Battery:");
      lcdSetText(uart1, 2, backupBattery);
      endResultMenu = LCD_BTN_RIGHT;
      if (lcdReadButtons(uart1) == LCD_BTN_CENTER && previousLCD != LCD_BTN_CENTER){// going back in the menu
        menuCount = 0;
        menuStay = 0;
        arbitraryVariable = 0;
        endResultMenu = 0;
      }
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
      lcdSetText(uart1, 1 , "Welcome");
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
  }
}


// actual lcd funciton
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
	}
	previousLCD = lcdReadButtons(uart1);
}
