#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "pulseblockheader.h"

int main() {
    
    randomSeed = 0;
    ticks = 0;
    
    int i = 0;
	drawRectangle(77, 10, 9, 9, foreground);

    while(1);

    return 0;
}
