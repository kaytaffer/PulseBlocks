#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void);
int getbtns(void);

int getsw(){    //gets bits 11:8 of Port D (the switches).
    return (PORTD >> 8) & 0x000F; //return 4 lsb data from switches SW4-SW1.
}

int getbtns() { //get bits 7:5 of Port D (buttons BTN4-BTN2.) D7 D6 D5 F1
    int res = ( (PORTD >> 4) & 0b01110 )
            | ( (PORTF >> 1) & 0b01 );
    
    return res; //3 lsb = current data from BTN4-BTN2.
}
