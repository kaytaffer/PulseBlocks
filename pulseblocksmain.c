#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h> /* Declarations of uint_8 etc */
#include "pulseblockheader.h" /*project declarations */

int main() {
    ticks = 0;
    
    showRandomPiece(foreground, DROPAREAROW, DROPAREACOLUMN);

    while(1);

    return 0;
}
