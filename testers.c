#include <stdio.h>
#include <stdint.h>  
#include <pic32mx.h>  
#include <string.h>
#include "pulseblockheader.h"

/* reads which buttons &| switches are toggled and lights a corresponding LED 
and prepares strings to print to display */
void villeIO() 
{
    volatile int* portE = (int*) 0xbf886110;
    char buttonsString[] = "    ";
    char switchesString[] = "    ";
    
    int buttons = getButtons();
    int switches = getSwitches();
    
    if(buttons & 0b01000) buttonsString[0] = '4';
    else buttonsString[0] = ' ';
    if(buttons & 0b0100) buttonsString[1] = '3';
    else buttonsString[1] = ' ';
    if(buttons & 0b0010) buttonsString[2] = '2';
    else buttonsString[2] = ' ';
    if(buttons & 0b0001) buttonsString[3] = '1';
    else buttonsString[3] = ' ';
    if(switches & 0b01000) switchesString[0] = '4';
    else switchesString[0] = ' ';
    if(switches & 0b0100) switchesString[1] = '3';
    else switchesString[1] = ' ';
    if(switches & 0b0010) switchesString[2] = '2';
    else switchesString[2] = ' ';
    if(switches & 0b0001) switchesString[3] = '1';
    else switchesString[3] = ' ';
    *portE = (switches << 4 ) | buttons;
}

int ticksSinceStart = 0;  
void ledTest() {       //increases the LED:s in a binary fashion each time it is called
    PORTE = ++ticksSinceStart;  
}
