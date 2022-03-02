#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

int main() {
    
    randomSeed = 0;
    ticks = 0;
    
    int i = 0;
	drawRectangle(77, 10, 9, 9, foreground);

    while(1);

    return 0;
}
