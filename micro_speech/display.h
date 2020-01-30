/* 
This sketch draws to the 64x48 pixel MicroOLED
  
  Hardware Connections:
    We'll be using the Qwiic I2C interface on the MicroOLED
==============================================================================*/

#ifndef DISPLAY_H_
#define DISPLAY_H_

void displaySplashScreen(void);
void displayText(const char* text);
void drawUp(void);
void drawRight(void);
void drawDown(void);
void drawLeft(void);
void displayReplayScreen(void);
void displayEndGame(void);
void displayComputerTurn(int level);
void displayYourTurn(void);

#endif  // DISPLAY_H_
