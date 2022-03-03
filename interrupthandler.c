/* interrupthandler.c
Interrupt Service Routine
See file COPYING for copyright information
*/

#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"

int blockFallQuotient = 0; //timeout count related to timer2
int buttonquotient = 0;
int pressedButton = 0;
/* Interrupt Service Routine  Handles all interrupts from I/O; switches, timers and the like. */
void userISR() {
      int moveLeft = 0;
      int moveRight = 0;

      if(IFS(0) & 0x0100) {  //timer 2 interrupt
            blockFallQuotient++;
            buttonquotient++;
            ticks++;
            IFSCLR(0) = 0x0100; // Resets the interrupt flag for timer 2 to 0.
            if (ticks == 0xFF) ticks = 0;
      }

      if (getButtons()){
          pressedButton = getButtons();
          if (!gameInProgress) {
              gameInProgress = 1;
          }
      }
      if(buttonquotient == 20){
            if(pressedButton & 0b1000) //BTN 1
                leftMove(foreground, PIXELMOVEAMOUNT);
            if(pressedButton & 0b100){
                while(falling(foreground, 1)); //BTN2: Hard drop: Makes elements in an array fall until one hits something
                pieceDropped();
            }
            if(pressedButton & 0b10)
                rotate(foreground);
            if(pressedButton & 0b1)
                rightMove(foreground, PIXELMOVEAMOUNT);

            convertPixels(foreground, background, display);
            displayImage(0, display);
            delay(200); //modifies how quickly the user may input new commands through the buttons
            pressedButton = 0;
            buttonquotient = 0;
      }

      if(blockFallQuotient == 30) {
          blockFallQuotient = 0;
          if(!falling(foreground, 1)){
              pieceDropped();
          }
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

