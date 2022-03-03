#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

void showMenu()
{
    clearScreen();
    showString("PULSE ", 0, 0, background);
    showString("BLOCKS", 7, 0, background);
    convertPixels(foreground, background, display);
    displayImage(0, display);
}

int main() {
    ticks = 0;
    nextPiece = ticks % 7;
    
    showMenu();
    
    while (!gameInProgress);
    
    clearScreen();
    
    /*Sets upp game background*/
    gameSetUp();
    convertPixels(foreground, background, display);
    displayImage(0, display);
    getNextPiece();
    getPiece();
    getNextPiece();

    while(1);

    return 0;
}
