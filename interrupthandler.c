/* interrupthandler.c
Interrupt Service Routine
See file COPYING for copyright information
*/

#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"

int blockFallQuotient = 0; //timeout count related to timer2
int buttonquotient = 0;
int pressedButton = 0;
int deltaSpeed = 0;
int gameSpeed = 0;
/* Interrupt Service Routine  Handles all interrupts from I/O; switches, timers and the like. */
void userISR() {
  int moveLeft = 0;
  int moveRight = 0;

  if(IFS(0) & 0x0100) {  //timer 2 interrupt
    blockFallQuotient++;
    buttonquotient++;
    ticks++;
    deltaSpeed++;
    IFSCLR(0) = 0x0100; // Resets the interrupt flag for timer 2 to 0.
      if (ticks == 0xFF) ticks = 0;
  }

  if((blockFallQuotient > (30 - gameSpeed) && (gameInProgress == 1) )) {
    blockFallQuotient = 0;
    if(!falling(foreground, 1)){                 
      pieceDropped();
    }
    convertPixels(foreground, background, display);
    displayImage(0, display);
    
  }

    if(deltaSpeed == 100) {   //timing related gamespeed modifier
    deltaSpeed = 0;
    if ((gameSpeed < MAXGAMESPEED) && (gameMode == 1))
      gameSpeed++;
  }

}

