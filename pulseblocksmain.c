#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

void showMenu()
{
    clearScreen();
    showString("PULSE ", 0, 0, background);
    showString("BLOCKS", 7, 0, background);
    showString("1 START", 21, 0, background);
    showString("2 HIGH", 35, 0, background);
    showString("  SCORE", 42, 0, background);
    convertPixels(foreground, background, display);
    displayImage(0, display);
}

void showEndMenu()
{
    clearScreen();
    showString("YOU ", 0, 0, background);
    showString("LOST", 7, 0, background);
    
    showInt(score, 21, 2, background);
    
    convertPixels(foreground, background, display);
    displayImage(0, display);
}

int main() {
    ticks = 0;
    nextPiece = ticks % 7;
    gameInProgress = 0;
    
    // -----
    /*showMenu(); //show startup menu
    while (!gameInProgress); // wait for game to start
    clearScreen(); // clear screen
    gameSetUp(); // set up background
    // start game
    getNextPiece();
    getPiece();
    getNextPiece();
    while(1);*/
    
    while (1) {
        showMenu(); //show startup menu
            
        while (!gameInProgress); // wait for game to start
        
        clearScreen(); // clear screen
        gameSetUp(); // set up background
        
        // start game
        getNextPiece();
        getPiece();
        getNextPiece();

        while(gameInProgress); // wait for game to end
        
        showEndMenu();
        while (!getButtons()); // wait for button input
    }
    return 0;
}
