#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

void showMenu()
{
    clearScreen(foreground);
    clearScreen(background);
    
    showLogo(5, 3, background);
    showString("1 START", 41, 0, background);
    showString("2 HIGH", 55, 0, background);
    showString("  SCORE", 62, 0, background);
    convertPixels(foreground, background, display);
    displayImage(0, display);
}

void showEndMenu()
{
    clearScreen(foreground);
    clearScreen(background);
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

    gameMode = 2;

    while (1) {
        showMenu(); //show startup menu
            
        while (!gameInProgress); // wait for game to start
        //ändra till !getButtons()
        if(gameInProgress){ 
            clearScreen(foreground);
            clearScreen(background); 
            gameSetUp(); // set up background
            
            // start game
            getNextPiece();
            getPiece();
            getNextPiece();

            while(gameInProgress); // wait for game to end

            showEndMenu();
            while (!getButtons()); // wait for button input
        }
        if(showHighScore)
        {
            clearScreen(foreground);
            clearScreen(background); 
        }

    }
    return 0;
}
