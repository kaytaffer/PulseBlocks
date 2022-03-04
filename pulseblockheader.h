#include <stdint.h>
#define PIXELROWS 128
#define PIXELCOLUMNS 32
#define PIXELMOVEAMOUNT 3
#define FONTHEIGHT 5
#define FONTWIDTH 3
#define BLOCKHEIGHT 3
#define BLOCKWIDTH 5

// game background constants

#define SCOREBOARDSTART 7
#define PULSEBOARDSTART 27
#define TEXTBOXHEIGHT (4 + FONTHEIGHT) // 9

#define GAMEBOARDHEIGHT (3 * 20 + 2) // 62
#define GAMEBOARDSTART (PIXELROWS - GAMEBOARDHEIGHT) // 66

#define NEXTBLOCKHEIGHT 10
#define NEXTBLOCKROW /*(GAMEBOARDSTART - NEXTBLOCKHEIGHT + 1)*/ 57
#define NEXTBLOCKWIDTH (3 * BLOCKWIDTH + 2) //14
#define NEXTBLOCKCOLUMN (PIXELCOLUMNS - NEXTBLOCKWIDTH) // 18

#define DROPAREAROW (GAMEBOARDSTART + 1)
#define DROPAREACOLUMN 10
#define DROPCENTERPIXELROW (DROPAREAROW + 4)
#define DROPCENTERPIXELCOLUMN (DROPAREACOLUMN + 4) 
#define NEXTAREAROW (NEXTBLOCKROW + 2)//59
#define NEXTAREACOLUMN (NEXTBLOCKCOLUMN + 2)//20

#define MAXGAMESPEED 29 

int gameSpeed; //manages how quickly blocks fall
int gameMode; //1-3: [time played, lines cleared, total points] which factor manages gameSpeed. 
int ticks;
int nextPiece;
int score;
int pulse;
int tetrominoCoord[2]; //The coordinates of an actively falling tetromino
int gameInProgress;
int showHighScore;

/* pulseblocksmain.c
TODO: Functions in active development. Move these functions from main to a better home when they're 
all grown up
*/
void gameSetUp();
void updateScore();
void updatePulse();
void showDigit(int digit, int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void showInt(int number, int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);

/* blockmovement.c
functions related to manipulating blocks
*/
int falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); /* Makes all elements in data array 
move to one lesser position each time function is called. Returns 1 if elements remain free to fall, return 0 
if they've hit something underneath*/ 
void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix left
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix right
void rotate(uint8_t data[PIXELROWS][PIXELCOLUMNS]); //rotates active blocks
void showPiece(int row, int col, int pieceID, uint8_t target[PIXELROWS][PIXELCOLUMNS]);
void getNextPiece();
void getPiece();

/* displaycommands.c
Functions related to OLED
*/ 
void iniateDisplay();               //Initiates the OLED
uint8_t spiManipulate(uint8_t);     //Configures OLED or writes to display (depending on command or data mode)
void displayImage(int x, uint8_t *bitmap);    //used to display the supplied bitmap to OLED with x offset
void setBit(uint8_t *target, int bit, uint8_t setTo); //
void convertPixels(uint8_t data1[PIXELROWS][PIXELCOLUMNS], uint8_t data2[PIXELROWS][PIXELCOLUMNS], uint8_t screen[512]); /* 
takes a 32*128 array of pixels for the screen and converts it into a one dimensional 512-element array in the 
correct order for the screen */
void horizontalLine(int startCol, int startRow, int length, uint8_t dest[PIXELROWS][PIXELCOLUMNS]); /* draws a 
horizontal line starting at startCol, startRow of specified length to the array dest */
void verticalLine(int startCol, int startRow, int length, uint8_t dest[PIXELROWS][PIXELCOLUMNS]); /* draws a 
vertical line starting at startCol, startRow of specified length to the array dest*/
void drawRectangle(int startRow, int startCol, int height, int width, uint8_t dest[PIXELROWS][PIXELCOLUMNS]); /*
draws a rectangle starting at startRow, startCol of specified height and width to array dest */
void writeToBackground(uint8_t data1[PIXELROWS][PIXELCOLUMNS], uint8_t data2[PIXELROWS][PIXELCOLUMNS]); /* writes 
the set contents of one data matrix onto another */
int charToElement(char c); /* for use with the font[][][]: converts chars 0-9, A-Z and a-z (+ space) to 
corresponding font-element */
void showChar(char c, int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]); /* adds a char to the 
array dest, starting at startRow, startCol */
void showString(char str[], int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]); /* adds a string 
to the array dest, starting at startRow, startCol */
void clearScreen(uint8_t data[PIXELROWS][PIXELCOLUMNS]);
void showImage(uint8_t *image,int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void showImage2(uint8_t image[23][21],int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);
void showLogo(int startRow, int startCol, uint8_t dest[PIXELROWS][PIXELCOLUMNS]);

/* displaydata.c
Data arrays and extern/global variables
*/ 
extern uint8_t display[512]; //Bitmap array for writing to the display
extern uint8_t foreground[PIXELROWS][PIXELCOLUMNS];  /* Matrix of elements, used for moving objects, to send 
to the display */
extern uint8_t background[PIXELROWS][PIXELCOLUMNS];  /* Matrix of elements, used for fixed objects, to send 
to the display */
const extern uint8_t tetrominos[7][2][4]; //matrix with bitmap arrays for the tetrominos
const uint8_t font[37][FONTHEIGHT][FONTWIDTH]; //a matrix of bitmap font elements
uint8_t logo[23][21];

/* gamecommands.c
Functions related to menus or changes in the game state
*/
int checkGameOver();/*Checks if a block already occupies the drop area, indicating game over*/
void pieceDropped();//what to do when piece hits something underneath it
int lineFull(int line);
void clearLine(int line);

/* input.c
I/O input
 */
int getSwitches();      //gets bits 11:8 of Port D (the switches).
int getButtons();       //get bits 7:5 of Port D (buttons BTN4-BTN2.) & bit 1 from PortF:  D7 D6 D5 F1
int getPulse();         //TODO: find right bits and make this work

/* interrupthandler.c
Interrupt Service Routine
*/
void userISR(); /* Handles all interrupts from I/O; switches, timers and the like. Has associated global 
variables */

/* assembly coded subroutines
pulseblocks.S
*/
void enableInterrupt(); //enables interrupt flags to trigger custom Interrupt Service Routine
void delay(int); /* helper function, creates delay by occupying processor for a while. Accepts milliseconds as 
argument. */                    

/* 
testers.c 
contains functions used for testing new code and implementations
*/
void villeIO(); /* reads which buttons &| switches are toggled and lights a corresponding LED 
and prepares strings to print to display */
void ledTest(); //increases the LED:s in a binary fashion each time it is called
void ledContent(int); //lights the LED:s in binary representation of argument up to 2^7.
