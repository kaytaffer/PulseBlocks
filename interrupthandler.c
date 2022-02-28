#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"

int timeOutCount2 = 0; //related to timer2
int ticksSinceStart = 0; //used for testing 
/* Interrupt Service Routine  Handles all interrupts from I/O; switches, timers and the like. */
void userISR() {
  if(IFS(0) & 0x0100) {  //timer 2 interrupt
    timeOutCount2++;
    IFSCLR(0) = 0x0100; // Resets the interrupt flag for timer 2 to 0. 
    PORTE = ++ticksSinceStart;  
  }
  if(timeOutCount2 == 9) {
    timeOutCount2 = 0;
    displayImage(0, foreground);
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

