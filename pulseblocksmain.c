#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

int main() {
    ticks = 0;
    nextPiece = ticks % 7;
    int pressedButton;
    
    getNextPiece();
    getPiece();
    getNextPiece();

    while(1) {
        if (getButtons()) {
            pressedButton = getButtons();
            if(pressedButton & 0b1000) //BTN 1
              leftMove(foreground, PIXELMOVEAMOUNT);
            if(pressedButton & 0b100){
              while(falling(foreground, 1)); //BTN2: Hard drop: Makes elements in an array fall until one hits something
              pieceDropped();
            }
            if(pressedButton & 0b10)
              rotate(foreground);
            if(pressedButton & 0b1)
              rightMove(foreground, PIXELMOVEAMOUNT);
        }
        if(!falling(foreground, 1)) pieceDropped();
        convertPixels(foreground, background, display);
        displayImage(0, display);
        if(checkGameOver()) {
            break;
        }
        showInt(tetrominoCoord[0], 37, 0, background);
        showInt(tetrominoCoord[1], 43, 0, background);
        delay(200);
    }
    
    while(1);

    return 0;
}
