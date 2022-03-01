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
    for(i = 8; i < 17; i++)
        foreground[1][i] = 1;

    while(1);

    return 0;
}
