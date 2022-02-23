/*

TODO Make project header file that makes mipslab.h obsolete

*/

//TODO implement camelCase for this function all over the place
void enable_interrupt();

/* I/O input
input.c
 */
int getSwitches();      //gets bits 11:8 of Port D (the switches).
int getButtons();       //get bits 7:5 of Port D (buttons BTN4-BTN2.) & bit 1 from PortF:  D7 D6 D5 F1
int getPulse();         //TODO: find right bits and make this work


/* Tester functions
testers.c contains functions used for testing new code and implementations*/
void villeIO(); /* reads which buttons &| switches are toggled and lights a corresponding LED 
and prepares strings to print to display */