/* gamecommands.c
Functions related to menus or changes in the game state
For copyright and licensing, see file COPYING */

#include <stdint.h> /* Declaration uint_8 etc */
#include "pulseblockheader.h" /*project declarations */
#include <pic32mx.h>

int checkGameOver(){ /*Checks if a block already occupies the drop area, indicating game over*/
    int gameOver = 0;
    if(background[DROPAREAROW + 6][DROPAREACOLUMN + 6])
        gameOver = 1;
    return gameOver;  
}

//what to do when piece hits something underneath it
void pieceDropped()
{
    writeToBackground(foreground, background);
    if (checkGameOver()){
        //TODO: Something
        ledTest();
    }
    updateScore();
    updatePulse(); // should be moved when pulse shit is implemented
    getPiece();
    getNextPiece();
}
