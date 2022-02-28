#include <stdio.h>
#include "pulseblockheader.h"

int forbidRightMove[] = { /* all odd numbers <= 255*/ };
int forbidLeftMove[] = { /* all ints n such that 0x8F < n <= oxFF*/ };

/*TODO 
void fillForbidRight() {
    for (int i = 1; i < 256; i+=2)
    {

    }

}
*/

/* TODO
void fillForbidLeft() {
    int j = 0;
    for (int i = 0x8F; i < 0x100; i++){
        forbidLeftMove[j] = i;
        j++;
    }
}
*/

/* Makes all elements in data array fall one move to one lesser position each time function is called */
int screenTransition; //associated to fallingLineRepeat
void fallingLineRepeat(){
    int i = 0; // iteration variable
    
    for (i = 0; i < 512; i++) {
        if (foreground[i] == 255) {
            foreground[i-1] = 255;
            foreground[i] = 0;
        }
    }
        if (screenTransition) {
        foreground[511] = 255; 
        screenTransition = 0;
    }
    if (foreground[384] == 255){ //prepares a screen switch when the line is at the bottom of a screen
        screenTransition = 1; //true
    }
}





/* Alternate approach

Two array method (probably wise either way)

Background array has two frames, the outer edge set black, the inner edge set clear.
For a left/right moving block, checks if pixel is light, then black and forbids movement.
Might cause bugs, when placing blocks close to each other. Hm, maybe use this for foreground array 
but exclude these values from falling. Suspect lot of special cases.

*/