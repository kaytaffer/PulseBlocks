/* mipslabfunc.c
   This file is mostly written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

    functions adapted for use in project PulseBlocks by K O'Flaherty

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"  

uint8_t spiManipulate(uint8_t data) { //Serial Peripheral Interface interfacing
	while(!(SPI2STAT & 0x08));  //while inte SPITBE: medans det finns något i SPI2TXB (memory mapped to SPI2BUF) registret väntar man
    SPI2BUF = data; //sen skrkivs det över från data
	while(!(SPI2STAT & 1)); //while inte SPIRBF: medans SPIRXB (receive buffer) inte är full, vänta
	return SPI2BUF; //Läserfrån SPI2BUF och tömmer SPIRXB
}

/* Initiates the OLED display*/
void initiateDisplay() {
	PORTFCLR = 0x10; //Data/Command pin to accept command mode
	delay(1); 		//The maximum SPI clock frequency is 10Mhz. 
	PORTFCLR = 0x40; //VDD display on
	delay(1000);
	
	spiManipulate(0xAE);
    PORTGCLR = 0x200; // reset display    
	delay(1);
	PORTGSET = 0x200; // no-reset / display normal operation
	delay(1);
	
	spiManipulate(0x8D);
	spiManipulate(0x14);
	
	spiManipulate(0xD9);
	spiManipulate(0xF1);
	
	PORTFCLR = 0x20; //turn off OLED power (VBAT)
	delay(1000);
	
	spiManipulate(0xA1);
	spiManipulate(0xC8);
	
	spiManipulate(0xDA);
	spiManipulate(0x20);
	
	spiManipulate(0xAF);
}

void displayImage(int x, uint8_t *bitmap) {
	int i, j; //iteration variables
	
	for(i = 0; i < 4; i++) {
	  PORTFCLR = 0x10; //Data/Command pin to accept command mode

		spiManipulate(0x22);
		spiManipulate(i);
		
		spiManipulate(x & 0xF);
		spiManipulate(0x10 | ((x >> 4) & 0xF));
		
	  PORTFSET = 0x10; //D/C pin to receive data mode
		
		for(j = 0; j < 128; j++)  //sends data to display buffer 1:s are white pixels
			spiManipulate(bitmap[i*128 + j]); 
	}
}

void displayPrint(void) {
	int i, j, k;
	char c;
	for(i = 0; i < 4; i++) {
		PORTFCLR = 0x10; //Data/Command pin to accept command mode
		spiManipulate(0x22);
		spiManipulate(i);
		
		spiManipulate(0x0);
		spiManipulate(0x10);
		
		PORTFSET = 0x10; //D/C pin to receive data mode
		for(j = 0; j < 16; j++) {
			c = textrows[i][j];
			if(!(c & 0x80)){
                for(k = 0; k < 8; k++)
				  spiManipulate(font[c*8 + k]);
            }
		}
	}
}

/*Function that fills a row (in a matrix with up to 4 rows) with up to 16 characters*/
void displayString(int row, char *c) {
	int i; //iterator variable
	for(i = 0; i < 16; i++)         //For the 16 spots in the character matrix
		if(*c) {
			textrows[row][i] = *c; //Sets the line contents to argument characters on argument line
			c++;                    //moves to next char
		} else
			textrows[row][i] = ' '; //then fills the rest of the line with empty space
  displayPrint();                     //calls function that interprets and prints symbols to screen 
}