#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "pulseblockheader.h"


int main() {

    int r, c;
    for (r = 0; r < 128; r++) {
        for (c = 0; c < 32; c++) {
            foreground[r][c] = 0;
        }
    }
    
    int i;
    for (i = 0; i < 32; i++) {
        foreground[0][i] = 1;
        foreground[126][i] = 1;
        foreground[127][i] = 1;
    }
    
     convertPixels(foreground, background, display);
    
    return 0;
}
