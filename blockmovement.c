#include <stdio.h>


int forbidRightMove[] = { /* all odd numbers <= 255*/ };

int forbidLeftMove[] = { /* all ints n such that 0x8F < n <= oxFF*/ };

void fillForbidRight() {
    for (int i = 1; i < 256; i+=2)
    {

    }

}



void fillForbidLeft() {
    int j = 0;
    for (int i = 0x8F; i < 0x100; i++){
        forbidLeftMove[j] = i;
        j++;
    }
}






/* Alternate approach

Two array method (probably wise either way)

Background array has two frames, the outer edge set black, the inner edge set clear.
For a left/right moving block, checks if pixel is light, then black and forbids movement.
Might cause bugs, when placing blocks close to each other. Hm, maybe use this for foreground array 
but exclude these values from falling. Suspect lot of special cases.

*/