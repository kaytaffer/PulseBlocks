#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

extern char hiScoreHolder[3];
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
    if(highScore < score){
        int i; //iterator var
        for(i = 0; i < 3;i++)
        showChar(hiScoreHolder[i], 0, 10 + 4 * i, background); //Writes fontrepresentation of hiScore to background-array

    }
    else{

    }
        showString("YOU ", 0, 0, background); //TODO flytta innanför else
        showString("LOST", 7, 0, background);

        showString("UR SCORE", 21, 0, background);
        showInt(score, 28, 2, background);

        showString("HIGH ", 42, 0, background);
        showString("SCORE", 49, 0, background);
        showInt(highScore, 56, 2, background);

        
    convertPixels(foreground, background, display);
    displayImage(0, display);

}

int main() {

    recordHighScore();

    ticks = 0;
    nextPiece = ticks % 7;
    gameInProgress = 0;


    gameMode = 2;

    while (1) {
        showMenu(); //show startup menu
            
        while (!gameInProgress); // wait for game to start
        //ändra till !getButtons()
        if(gameInProgress == 1){ 
            clearScreen(foreground);
            clearScreen(background); 
            gameSetUp(); // set up background
            
            // start game
            score = -10;
            getNextPiece();
            getPiece();
            getNextPiece();

            while(gameInProgress); // wait for game to end

            showEndMenu();
            while (!getButtons()); // wait for button input
        }
        if(gameInProgress) // == 2 high score 
        {
            clearScreen(foreground);
            clearScreen(background); 
        }

    }
    return 0;
}
