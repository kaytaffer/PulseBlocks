#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "pulseblockheader.h"

int timeOutCount = 0;
int ticksSinceStart = 0;
/* Interrupt Service Routine */
void userISR() {
  if(IFS(0) & 0x0100) {  //timer 2 interrupt
    timeOutCount++;
    IFSCLR(0) = 0x0100; // Resets the interrupt flag for timer 2 to 0.   
  }
  if(IFS(0) & 0x080000){ //Switch 4 interrupt
  IFSCLR(0) = 0x080000; // Resets the interrupt flag for SW4 to 0. 
  volatile int* portE = (int*) 0xbf886110;
  *portE = ++ticksSinceStart;
  }

  if(timeOutCount == 9) {
    timeOutCount = 0;
    displayImage(0, foreground);
  }
  
}


/* Makes all elements in data array fall one move to one lesser position each time function is called
TODO, reimagine this function with new display-to-screen-functions to come. */
int screenTransition;
void fallingLine(){
    int i = 0; // iteration variable
    
    for (i = 0; i < 512; i++) {
        if (foreground[i] == 255) {
            foreground[i-1] = 255;
            foreground[i] = 0;
        }
    }
        if (screenTransition) {
        foreground[511] = 255; 
        screenTransition = 0;               
    }
    if (foreground[384] == 255){ //prepares a screen switch when the line is at the bottom of a screen
        screenTransition = 1; //true
    }
}

int main() {

	while(1){
        fallingLine();
        delay(10);
    }

return 0;
}

