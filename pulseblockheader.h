/*

TODO Make project header file that makes mipslab.h obsolete

*/
#include <stdint.h>


/*
TODO Functions in active development. Move these functions from main to a better home when they're all grown up
*/
void userISR();//has associated global variables 
void fallingLine(); //has associated global variables 


/* assembly coded subroutines
pulseblocks.S
*/
void enableInterrupt(); //enables interrupt flags to trigger custom Interrupt Service Routine
void delay(int); /* helper function, creates delay by occupying processor for a while. Accepts milliseconds as 
argument. */                    

/* I/O input
input.c
 */
int getSwitches();      //gets bits 11:8 of Port D (the switches).
int getButtons();       //get bits 7:5 of Port D (buttons BTN4-BTN2.) & bit 1 from PortF:  D7 D6 D5 F1
int getPulse();         //TODO: find right bits and make this work

/* Functions related to OLED
displaycommands.c
*/ 
void iniateDisplay();               //Initiates the OLED
uint8_t spiManipulate(uint8_t);     //Configures OLED or writes to display (depending on command or data mode)
void displayImage(int x, uint8_t *bitmap);    //used to display the supplied bitmap to OLED with x offset
void displayPrint();       //Used by displayString to interprets and prints symbols to screen 
void displayString(int line, char *s);  //Function that fills a row (in a matrix with up to 4 rows) with up to 16 characters/


/* Tester functions
testers.c 
contains functions used for testing new code and implementations*/
void villeIO(); /* reads which buttons &| switches are toggled and lights a corresponding LED 
and prepares strings to print to display */


/* Data arrays and extern/global variables
displaydata.c
*/ 
extern uint8_t foreground[128*4];  /* Bitmap array for writing to the display, used for moving objects*/
extern uint8_t background[128*4];  /* Bitmap array for writing to the display, used for fixed objects*/
extern char textrows[4][16]; //allows for saving 16-character strings in 4 rows
extern const uint8_t const font[128*8]; //A library of that's used to convert characters into their corresponding symbols