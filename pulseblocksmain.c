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

void showHighScore(){
    clearScreen(foreground);
    clearScreen(background); 

    showString("CURRENT", 0, 0, background);
    showString("HIGH", 7, 0, background);
    showString("SCORE", 14, 0, background);
    showInt(highScore, 28, 2, background);    

    showString("HELD", 42, 0, background);
    showString("BY", 49, 0, background);
    int i; //iterator var
        for(i = 0; i < 3;i++)
            showChar(hiScoreHolder[i], 56, 10 + 4 * i, background); //Writes fontrepresentation of hiScore to background-array

    convertPixels(foreground, background, display);
    displayImage(0, display);
    delay(500);
    while (!getButtons()); // wait for button input
}

void showEndMenu()
{

    clearScreen(foreground);
    clearScreen(background);
    if(highScore < score){
        recordHighScore();
        showHighScore();
    }
    else{
        showString("YOU ", 0, 0, background); //TODO flytta innanför else
        showString("LOST", 7, 0, background);

        showString("UR SCORE", 21, 0, background);
        showInt(score, 28, 2, background);

        showString("HIGH ", 42, 0, background);
        showString("SCORE", 49, 0, background);
        showInt(highScore, 56, 2, background);
    }
}

int main() {

    ticks = 0;
    nextPiece = ticks % 7;
    gameInProgress = 0;
    gameMode = 2;

    while (1) {
        showMenu(); //show startup menu
        delay(500);

        while (!getButtons()); // wait for game to start
        if(getButtons() == 1){
                T2CONSET = 0x8000;              //start timer 
            clearScreen(foreground);
            clearScreen(background); 
            gameSetUp(); // set up background
            
            // start game
            score = 0;
            getNextPiece();
            getPiece();
            getNextPiece();

            while(gameInProgress == 1); // wait for game to end

            T2CONCLR = 0x8000;              //stop timer 
            showEndMenu();
            while (!getButtons()); // wait for button input
        }
        if(getButtons() == 2) // == 2 high score 
        {
            showHighScore();
            gameInProgress = 0;
        }

    }
    return 0;
}
