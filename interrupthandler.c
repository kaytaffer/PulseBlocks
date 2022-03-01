#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"

int blockFallQuotient = 0; //timeout count related to timer2
int moveSidewaysQuotient = 0;
/* Interrupt Service Routine  Handles all interrupts from I/O; switches, timers and the like. */
void userISR() {
  int moveLeft = 0;
  int moveRight = 0;

  if(IFS(0) & 0x0100) {  //timer 2 interrupt
    blockFallQuotient++;
    moveSidewaysQuotient++;
    ticks++;
    IFSCLR(0) = 0x0100; // Resets the interrupt flag for timer 2 to 0.
      if (ticks == 0xFF) ticks = 0;
  }
   
  if(getButtons())
    moveSidewaysQuotient = 2; 
  if (moveSidewaysQuotient == 2){
    moveSidewaysQuotient = 0;
    if (getButtons()) {
      if(getButtons() & 0b1000)
        leftMove(foreground, PIXELMOVEAMOUNT);
      if(getButtons() & 0b1)
        rightMove(foreground, PIXELMOVEAMOUNT);
      convertPixels(foreground, background, display);
      displayImage(0, display);
    }
  }

  if(blockFallQuotient == 9) {
    blockFallQuotient = 0;
    falling(foreground, 1);
    convertPixels(foreground, background, display);
    displayImage(0, display);
  }

  if(IFS(0) & 0x080000){ //Switch 4 interrupt
    IFSCLR(0) = 0x080000; // Resets the interrupt flag for SW4 to 0. 
  }

  if(IFS(0) & 0x008000){ //Switch 3 interrupt
  IFSCLR(0) = 0x008000; // Resets the interrupt flag for SW3 to 0. 
  }

  if(IFS(0) & 0x000800){ //Switch 2 interrupt
  IFSCLR(0) = 0x000800; // Resets the interrupt flag for SW2 to 0. 
  }

  if(IFS(0) & 0x000080){ //Switch 1 interrupt
  IFSCLR(0) = 0x000080; // Resets the interrupt flag for SW1 to 0. 
  }
  
}

