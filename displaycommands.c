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

// takes a target uint8_t, of which the bit with index "bit" is changed to "setTo"
void setBit(uint8_t *target, int bit, uint8_t setTo)
{
    *target = *target & ~(1 << bit); // mask the bit that should be changed
    *target += (int) setTo << bit; // change the bit
}

// takes a 32*128 array of pixels for the screen and converts it into a one dimensional 512-element array
// in the correct order for the screen
void convertPixels(uint8_t data1[128][32], uint8_t data2[128][32], uint8_t screen[512]) {
    int r, c;               // current row and column
    int scElement = 127;    // element of the screen array
    int bit;                // what bit of the uint8_t should be changed
    int ofs;                // offset from scElement
    for (r = 0; r < 128; r++) { // go though rows
        bit = 0;    // reset bit
        ofs = 0;    // reset ofs
        for (c = 0; c < 32; c++) { // go through cols
            // the element of screen is calculated (128 is +1 col)
            // the specified element is set to 1 if the corresponding pixel in data1 OR data2 is one
            setBit(&screen[scElement + ofs * 128], bit, (data1[r][c] | data2[r][c]));
            bit++;
            if(bit == 8) { //if bit is 8 it should be reset and ofs should increase (next element)
                bit = 0;
                ofs++;
            }
        }
        scElement--; //for the next row: scElement decreases!
    }
}

void horizontalLine(int startCol, int startRow, int length, uint8_t dest[128][32])
{
    int c;
    for (c = startCol; c < startCol + length && c < 32; c++) {
        dest[startRow][c] = 1;
    }
}

void verticalLine(int startCol, int startRow, int length, uint8_t dest[128][32])
{
    int r;
    for (r = startRow; r < startRow + length && r < 128; r++) {
        dest[r][startCol] = 1;
    }
}

void drawRectangle(int startRow, int startCol, int height, int width, uint8_t dest[128][32])
{
    horizontalLine(startCol, startRow, width, dest);
    horizontalLine(startCol, startRow + height - 1, width, dest);
    verticalLine(startCol, startRow, height, dest);
    verticalLine(startCol + width - 1, startRow, height, dest);
}

int charToElement(char c)
{
    // in the array, 0-9 is element 0-9
    // and A-Z is element 10-35
    // space is 36
    if(c >= '0' && c <= '9') return (int) c - '0';
    if(c >= 'A' && c <= 'Z') return (int) c - 'A' + 10;
    if(c >= 'a' && c <= 'z') return (int) c - 'a' + 10;
    else return 36;
}

void showChar(char c, int startRow, int startCol, uint8_t dest[128][32])
{
    int x, y;
    for (y = 0; y < 3; y++) {
        for (x = 0; x < 5; x++)
            dest[x + startRow][y + startCol] = villefont[charToElement(c)][x][y];
    }
}

void showString(char str[], int startRow, int startCol, uint8_t dest[128][32])
{
    int i = 0;
    for (i = 0; str[i]; i++)
        showChar(str[i], startRow, (startCol + 4 * i), dest);
}
