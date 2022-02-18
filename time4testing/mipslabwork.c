/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <string.h>

void fallingLine();

int mytime = 0x5957;
int timeoutcount = 0;
int ticks = 0;
short imageFourth = 1;
int screenTransition = 0;

char textstring[] = "text, more text, and even more text!";

uint8_t image1[] = {
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 0,
    
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 0,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 0,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 0,
};

uint8_t image2[] = {
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
};

uint8_t image3[] = {
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
};

uint8_t image4[] = {
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,

    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
};

/* Interrupt Service Routine */
void user_isr( void )
{
    return;
}

/* Lab-specific initialization goes here */
void labinit( void ) // £
{
    volatile int* trise = (int*) 0xbf886100;
    *trise = *trise | 0xFF00;
    
    TRISD = TRISD | 0x0FE0;          //0000 1111 1110 0000
    
    T2CON = 0x70;                   // stops timer, clear control register
    TMR2 = 0x0;                     // clear timer register
    PR2 = 31250;                    // load period register
    
    IFSCLR(0) = 0x0100;
    IPCSET(0) = 0x0C + 0x1;
    IECSET(0) = 0x100;
    
    T2CONSET = 0x8000;              //start timer
    
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    //lampor!
    volatile int* porte = (int*) 0xbf886110;
    char buttonsString[] = "    ";
    char switchesString[] = "    ";
    
    int buttons = getbtns();
    int switches = getsw();
    
    /*if(buttons & 0b01000) buttonsString[0] = '4';
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
    else switchesString[3] = ' ';*/
    
    *porte = (switches << 4 ) | buttons;
    
    if(IFS(0) & 0x0100) {
        IFSCLR(0) = 0x0100;
        timeoutcount++;
        if(1/*timeoutcount == 9*/) {
            timeoutcount = 0;
            
            fallingLine();

            //display_string(0, buttonsString);
            //display_string(1, switchesString);
            //display_string(2, "");
            //display_string(3, "");
            //display_update();                                  
            //*porte = ticks++;
        }
    }
    
}

void fallingLine()
{    
    int i; //loop variable

    switch (imageFourth){ //imageFourth is global variable
        case 1:
            if (screenTransition) {                
                image1[31] = 0; image1[63] = 0; image1[95] = 0; image1[127] = 0;
                image4[0] = 255; image4[32] = 255; image4[64] = 255; image4[96] = 255;
                screenTransition = 0;
                display_image(0, image4);   
            }

            else {        
                for(i = 0; i < 128; i++) {
                    if (image1[i] == 0) {
                        image1[i-1] = 0;
                        image1[i] = 255;
                    }
                }    
            }           

            if (image1[0] == 0){ //prepares a screen switch when the line is at the bottom of a screen
                screenTransition = 1; //true
                imageFourth++;        
            }
            display_image(96, image1);             
            break;
        case 2:
            if (screenTransition) {
                image2[31] = 0; image2[63] = 0; image2[95] = 0; image2[127] = 0;
                image1[0] = 255; image1[32] = 255; image1[64] = 255; image1[96] = 255;
                screenTransition = 0;    
                display_image(96, image1);     
            }
            else {        
                for(i = 0; i < 128; i++) {
                    if (image2[i] == 0) {
                        image2[i-1] = 0;
                        image2[i] = 255;
                    }
                }    
            }          
            if (image2[0] == 0){ //prepares a screen switch when the line is at the bottom of a screen
                screenTransition = 1; //true
                imageFourth++;
            }
            display_image(64, image2);            
            break;
        case 3:
            if (screenTransition) {
                image3[31] = 0; image3[63] = 0; image3[95] = 0; image3[127] = 0;
                image2[0] = 255; image2[32] = 255; image2[64] = 255; image2[96] = 255;
                screenTransition = 0;
                display_image(64, image2);                     
            }
            else {        
                for(i = 0; i < 128; i++) {
                    if (image3[i] == 0) {
                        image3[i-1] = 0;
                        image3[i] = 255;
                    }
                }    
            }          
            if (image3[0] == 0){ //prepares a screen switch when the line is at the bottom of a screen
                screenTransition = 1; //true
                imageFourth++;
            }
            display_image(32, image3);            
            break;            
        case 4:
            if (screenTransition) {
                image4[31] = 0; image4[63] = 0; image4[95] = 0; image4[127] = 0;
                image3[0] = 255; image3[32] = 255; image3[64] = 255; image3[96] = 255;
                screenTransition = 0;
                display_image(32, image3);    
            }
            else {        
                for(i = 0; i < 128; i++) {
                    if (image4[i] == 0) {
                        image4[i-1] = 0;
                        image4[i] = 255;
                    }
                }    
            }         
            if (image4[0] == 0){ //prepares a screen switch when the line is at the bottom of a screen
                screenTransition = 1; //true
                imageFourth++;
                if (imageFourth == 5) //Resets to topmost screen
                    imageFourth = 1;
            }
            display_image(0, image4);             
            break;
        default: 
            for(i = 0; i < 128; i++){
                image1[i] = 0;
                image2[i] = 0;
                image3[i] = 0;
                image4[i] = 0;                 
            }
            display_image(96, image1);
            display_image(64, image2);
            display_image(32, image3);
            display_image(0, image4);               
            break;
    }



    /*
    if (image[31] == 0) 
        image[127] = 0;
    */
}