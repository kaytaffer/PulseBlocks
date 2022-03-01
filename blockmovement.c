#include <stdio.h>
#include "pulseblockheader.h"

uint8_t finalFall = 0;
void falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    if(finalFall){                                     //TODO, flytta till och låta en annan funktion hantera allt detta
        finalFall = 0;                               
        writeToBackground(foreground, background);  //If there's a white pixel
        drawRectangle(77, 10, 9, 9, foreground);     //TODO, remove test rectangle
    }
    else {
        for(r = PIXELROWS - 1; r >= 0; r--){        //row by row
            for(c = 0; c < PIXELCOLUMNS; c++){      //column by column
                if(data[r][c] == 1){                //If there's a white pixel
                    data[r][c] = 0;                 //make pixel black
                    data[r + pixelmoveamount][c] = 1;   //and make the one underneath white
                    if (background[r + pixelmoveamount + 1][c]){
                        finalFall = 1;
                    }
                }
            }
        }
    }
}

void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    for(c = 0; c < PIXELCOLUMNS; c++){          //column by column
        for(r = PIXELROWS - 1; r >= 0; r--) {   //row by row
            if(data[r][c]){                     //If there's a white pixel
                if(background[r][c-1]){         //if at the border
                    r = 0;                      //forbids any more moves
                    c = PIXELCOLUMNS;
                }
                else {                          //otherwise
                    data[r][c] = 0;                 //make pixel black
                    data[r][c - pixelmoveamount] = 1; //and make the one to the left white
                }
            }
        }
    }
}
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    for(c = PIXELCOLUMNS - 1; c >= 0; c--){     //column by column
        for(r = PIXELROWS - 1; r >= 0; r--) {   //row by row
            if(data[r][c]){                     //If there's a white pixel
                if(background[r][c+1]){         //if at the border
                    r = 0;                      //forbids any more moves
                    c = 0;
                }
                else {                          //otherwise
                    data[r][c] = 0;                 //make pixel black
                    data[r][c + pixelmoveamount] = 1;   //and make the one to the right white
                }
            }
        }
    }
}


void rotate(uint8_t data[PIXELROWS][PIXELCOLUMNS]) { //rotates active blocks

    //TODO implement
}

void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix left
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount); //moves all elements in matrix right

void showRandomPiece(uint8_t target[PIXELROWS][PIXELCOLUMNS])
{
    int r, c;
    for (r = 0; r < 2 * 3; r++) {
        for (c = 0; c < 4 * 3; c++) {
            target[r + 5][c + 5] = tetrominos[ticks % 7][r / 3][c / 3];
        }
    }
}

