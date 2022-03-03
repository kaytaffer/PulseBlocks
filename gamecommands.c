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
    if (checkGameOver()){
        //TODO: Something
        
    }
    updateScore();
    updatePulse(); // should be moved when pulse shit is implemented
    getPiece();
    getNextPiece();
}

int lineFull(int line) {
    int c;
    for (c = 2; c < PIXELCOLUMNS - 1; c++) {
        if (!background[line][c]) return 0;
    }
    return 1;
}

void clearLine(int line) {
    int c, r, i;
    for (c = 2; c < PIXELCOLUMNS - 4; c++) {
        for (r = -1; r < 2; r++)
            background[line + r][c] = 0;
    }
    for (r = line; r > GAMEBOARDSTART + 4; r--) {
        for (c = 2; c < PIXELCOLUMNS - 1; c++) {
            background[r - 1][c] = background[r-3 - 1][c];
            background[r][c] = background[r-3][c];
            background[r + 1][c] = background[r-3 + 1][c];
        }
    }
    for (i = 2; i < PIXELCOLUMNS - 2; i++) {
        background[GAMEBOARDSTART + 1][c] = 0;
        background[GAMEBOARDSTART + 2][c] = 0;
        background[GAMEBOARDSTART + 3][c] = 0;
    }
    score++;
}
