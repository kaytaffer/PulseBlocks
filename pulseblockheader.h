#include <stdint.h>

#define PIXELROWS 128
#define PIXELCOLUMNS 32
#define PIXELMOVEAMOUNT 3
#define FONTHEIGHT 5
#define FONTWIDTH 3
int randomSeed;
int ticks;

/* Functions in active development. Move these functions from main to a better home when they're all grown up
pulseblocksmain.c
*/
void gameSetUp();

/* functions related to manipulating blocks
blockmovement.c
*/
int falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); /* Makes all elements in data array move to one lesser 
position each time function is called. Returns 1 if elements remain free to fall, return 0 if they've hit something underneath*/ 
void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix left
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix right
void rotate(uint8_t data[PIXELROWS][PIXELCOLUMNS]); //rotates active blocks
void showRandomPiece(uint8_t target[PIXELROWS][PIXELCOLUMNS]);

/* Interrupt Service Routine
interrupthandler.c */
void userISR(); //Handles all interrupts from I/O; switches, timers and the like. Has associated global variables 

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
void setBit(uint8_t *target, int bit, uint8_t setTo); //
void convertPixels(uint8_t data1[PIXELROWS][PIXELCOLUMNS], uint8_t data2[PIXELROWS][PIXELCOLUMNS], uint8_t screen[512]); //
void horizontalLine(int startCol, int startRow, int length, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void verticalLine(int startCol, int startRow, int length, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void drawRectangle(int startRow, int startCol, int height, int width, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void writeToBackground(uint8_t data1[PIXELROWS][PIXELCOLUMNS], uint8_t data2[PIXELROWS][PIXELCOLUMNS]); //writes the set contents of one data matrix onto another


/* Tester functions
testers.c 
contains functions used for testing new code and implementations*/
void villeIO(); /* reads which buttons &| switches are toggled and lights a corresponding LED 
and prepares strings to print to display */
void ledTest(); //increases the LED:s in a binary fashion each time it is called

/* Data arrays and extern/global variables
displaydata.c
*/ 
extern uint8_t display[512]; //Bitmap array for writing to the display
extern uint8_t foreground[PIXELROWS][PIXELCOLUMNS];  /* Matrix of elements, used for moving objects, to send to the display */
extern uint8_t background[PIXELROWS][PIXELCOLUMNS];  /* Matrix of elements, used for fixed objects, to send to the display */

extern char textrows[4][16]; //allows for saving 16-character strings in 4 rows
extern const uint8_t const font[128*8]; //A library that's used to convert characters into their corresponding symbols

extern uint8_t tetrominos[7][2][4];

/* related to font and writing strings */
uint8_t villefont[37][FONTHEIGHT][FONTWIDTH];
int charToElement(char c);
void showChar(char c, int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void showString(char str[], int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
