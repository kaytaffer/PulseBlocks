/*
input.c 
This file contains functions relating to inputs from the Basic I/O Shield
See file COPYING for copyright information
*/
#include <stdint.h> //definitions of uint_t and the like
#include <pic32mx.h> //defines for chipkit addresses etc

int getSwitches(){    //gets bits 11:8 of Port D (the switches).
    return (PORTD >> 8) & 0x000F; //return 4 lsb data from switches SW4-SW1.
}

int getButtons() { //get bits 7:5 of Port D (buttons BTN4-BTN2.) & bit 1 from PortF:  D7 D6 D5 F1
    int res = ( (PORTD >> 4) & 0b01110 )
            | ( (PORTF >> 1) & 0b01 );
    
    return res; //4 lsb = current data from BTN4-BTN2.
}

//TODO: find right bits and make this work
int getPulse() {
    int res = ( PORTB );

    return res; 
}