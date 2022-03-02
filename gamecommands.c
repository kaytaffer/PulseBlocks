/* gamecommands.c
Functions related to menus or changes in the game state
For copyright and licensing, see file COPYING */

#include <stdint.h> /* Declaration uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

int checkGameOver(){ //TODO: implement
    int gameOver = 0;
        


    return gameOver;  
}

//what to do when piece dropped
void pieceDropped()
{
    writeToBackground(foreground, background);
    updateScore();
    updatePulse(); // should be moved when pulse shit is implemented
    checkGameOver();
    getPiece();
    getNextPiece();
}
