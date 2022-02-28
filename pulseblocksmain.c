#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "pulseblockheader.h"

#define COLS 10
#define ROWS 20
#define STARTROW 22

int board[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0}
    /*{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}*/
};

void setThreeBits(uint8_t *target, int offset, int setTo)
{
    *target = *target & ~(0b0111 << offset); //mask target
    if(setTo) *target += 0b0111 << offset; //set three bits to 1 if setTo is 1 otherwise leave as 0
}

void setBit(uint8_t *target, int bit, int setTo)
{
    *target = *target & ~(1 << bit);
    *target += setTo << bit;
}

void convertBoard(int arr[ROWS][COLS], uint8_t screen[512]) {
    int startElement;
    int i;
    for (i = 0; i < ROWS; i++) {
        startElement = 127 - 3 * i;
        // 105 104
        
        //pixel 0 (arr[i][0])
        setThreeBits(&screen[startElement],     1, arr[i][0]);
        setThreeBits(&screen[startElement - 1], 1, arr[i][0]);
        setThreeBits(&screen[startElement - 2], 1, arr[i][0]);
        
        //pixel 1 (arr[i][1])
        setThreeBits(&screen[startElement],     4, arr[i][1]);
        setThreeBits(&screen[startElement - 1], 4, arr[i][1]);
        setThreeBits(&screen[startElement - 2], 4, arr[i][1]);
        
        //pixel 2 (arr[i][2])
        setBit(&screen[startElement],       7, arr[i][2]);
        setBit(&screen[startElement + 128], 0, arr[i][2]);
        setBit(&screen[startElement + 128], 1, arr[i][2]);
        
        setBit(&screen[startElement - 1],       7, arr[i][2]);
        setBit(&screen[startElement + 128 - 1], 0, arr[i][2]);
        setBit(&screen[startElement + 128 - 1], 1, arr[i][2]);
        
        setBit(&screen[startElement - 2],       7, arr[i][2]);
        setBit(&screen[startElement + 128 - 2], 0, arr[i][2]);
        setBit(&screen[startElement + 128 - 2], 1, arr[i][2]);
        
        //pixel 3 (arr[i][3])
        setThreeBits(&screen[startElement + 128],     2, arr[i][3]);
        setThreeBits(&screen[startElement + 128 - 1], 2, arr[i][3]);
        setThreeBits(&screen[startElement + 128 - 2], 2, arr[i][3]);
        
        //pixel 4 (arr[i][4])
        setThreeBits(&screen[startElement + 128],     5, arr[i][4]);
        setThreeBits(&screen[startElement + 128 - 1], 5, arr[i][4]);
        setThreeBits(&screen[startElement + 128 - 2], 5, arr[i][4]);
        
        //pixel 5 (arr[i][5])
        setThreeBits(&screen[startElement + 256],     0, arr[i][5]);
        setThreeBits(&screen[startElement + 256 - 1], 0, arr[i][5]);
        setThreeBits(&screen[startElement + 256 - 2], 0, arr[i][5]);
        
        //pixel 6 (arr[i][6])
        setThreeBits(&screen[startElement + 256],     3, arr[i][6]);
        setThreeBits(&screen[startElement + 256 - 1], 3, arr[i][6]);
        setThreeBits(&screen[startElement + 256 - 2], 3, arr[i][6]);
        
        //pixel 7 (arr[i][7])
        setBit(&screen[startElement + 256], 6, arr[i][7]);
        setBit(&screen[startElement + 256], 7, arr[i][7]);
        setBit(&screen[startElement + 384], 0, arr[i][7]);
        
        setBit(&screen[startElement + 256 - 1], 6, arr[i][7]);
        setBit(&screen[startElement + 256 - 1], 7, arr[i][7]);
        setBit(&screen[startElement + 384 - 1], 0, arr[i][7]);
        
        setBit(&screen[startElement + 256 - 2], 6, arr[i][7]);
        setBit(&screen[startElement + 256 - 2], 7, arr[i][7]);
        setBit(&screen[startElement + 384 - 2], 0, arr[i][7]);
        
        //pixel 8 (arr[i][8])
        setThreeBits(&screen[startElement + 384], 1, arr[i][8]);
        setThreeBits(&screen[startElement + 384 - 1], 1, arr[i][8]);
        setThreeBits(&screen[startElement + 384 - 2], 1, arr[i][8]);
        
        //pixel 9 (arr[i][9])
        setThreeBits(&screen[startElement + 384], 4, arr[i][9]);
        setThreeBits(&screen[startElement + 384 - 1], 4, arr[i][9]);
        setThreeBits(&screen[startElement + 384 - 2], 4, arr[i][9]);
        
    }
}

int main() {

	/*while(1){
        fallingLineRepeat();
        delay(10);
    }*/
    convertBoard(board, foreground);
    return 0;
}

