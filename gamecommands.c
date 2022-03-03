/* gamecommands.c
Functions related to menus or changes in the game state
For copyright and licensing, see file COPYING */

#include <stdint.h> /* Declaration uint_8 etc */
#include "pulseblockheader.h" /*project declarations */
#include <pic32mx.h>

int checkGameOver(){ /*Checks if a block already occupies the drop area, indicating game over*/
    int gameOver = 0;
    if(background[DROPCENTERPIXELROW][DROPCENTERPIXELCOLUMN])
        gameOver = 1;
    return gameOver;  
}

//what to do when piece hits something underneath it
void pieceDropped()
{
    writeToBackground(foreground, background);
    int r;
    for (r = PIXELROWS - 2; r > GAMEBOARDSTART + 4; r--) { // check all pixel rows
        if (lineFull(r)) { // if line full
            clearLine(r); // remove line
            score += 10; // add score (30 per block line)
            r++;
        }
    }
    updateScore();
    updatePulse(); // should be moved when pulse shit is implemented
    if (checkGameOver()){
        ledContent(0xaa);
        gameInProgress = 0;
        return;
    }
    getPiece();
    getNextPiece();
}

int lineFull(int line) {
    int c;
    for (c = 1; c < PIXELCOLUMNS - 1; c++) { // check all columns
        if (!background[line][c]) return 0; // if a pixel is 0 then line not full
    }
    return 1; // otherwise line full
}

void clearLine(int line) {
    int c, r, i;
    for (c = 1; c < PIXELCOLUMNS - 4; c++) { // go through columns of game board
        background[line][c] = 0; //clear
        
    }
    for (r = line; r > GAMEBOARDSTART + 4; r--) { // start looking down from top of game board, downwards
        for (c = 1; c < PIXELCOLUMNS - 1; c++) { // go through all columns of game board
            background[r][c] = background[r-1][c];
        }
    }
    for (i = 2; i < PIXELCOLUMNS - 2; i++) {
        background[GAMEBOARDSTART + 1][i] = 0;
    }
    convertPixels(foreground, background, display);
    displayImage(0, display);
    delay(10);
}
