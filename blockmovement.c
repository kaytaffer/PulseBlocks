#include <stdio.h>
#include "pulseblockheader.h"

void falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    for(r = PIXELROWS - 1; r >= 0; r--){ 
        for(c = 0; c < PIXELCOLUMNS; c++){
            if(data[r][c]){
                data[r][c] = 0;
                data[r + pixelmoveamount][c] = 1;
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
            if(data[r][c]){                     //
                data[r][c] = 0;                 
                data[r][c - pixelmoveamount] = 1;
            }
        }
    }
}
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    for(c = PIXELCOLUMNS - 1; c >= 0; c--){
        for(r = PIXELROWS - 1; r >= 0; r--) {
            if(data[r][c]){
                data[r][c] = 0;
                data[r][c + pixelmoveamount] = 1;
            }
        }
    }
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
