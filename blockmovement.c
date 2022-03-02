/* blockmovement.c
functions related to manipulating blocks
For copyright and licensing, see file COPYING */

#include "pulseblockheader.h" /*project declarations */

uint8_t rotationState = 0;
uint8_t tetrominoType = 0;

int falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    uint8_t freefall = 1;
    int r, c; //iterator variables for rows and columns
    for(r = PIXELROWS - 1; r >= 0; r--){        //row by row
        for(c = 0; c < PIXELCOLUMNS; c++){      //column by column
            if(data[r][c] == 1){                //If there's a white pixel
                data[r][c] = 0;                 //make pixel black
                data[r + pixelmoveamount][c] = 1;   //and make the one underneath white
                if (background[r + pixelmoveamount + 1][c]){
                    freefall = 0;
                }
            }
        }
    }
    return freefall;
}

void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r, c; //iterator variables for rows and columns
    for(c = 0; c < PIXELCOLUMNS; c++){          //column by column
        for(r = PIXELROWS - 1; r >= 0; r--) {   //row by row
            if(data[r][c]){                     //If there's a white pixel
                if(background[r][c-1]){         //if at the border
                    r = 0;                      //forbids any more moves
                    c = PIXELCOLUMNS;
                }
                else {                          //otherwise
                    data[r][c] = 0;                 //make pixel black
                    data[r][c - pixelmoveamount] = 1; //and make the one to the left white
                }
            }
        }
    }
}
void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r, c; //iterator variables for rows and columns
    for(c = PIXELCOLUMNS - 1; c >= 0; c--){     //column by column
        for(r = PIXELROWS - 1; r >= 0; r--) {   //row by row
            if(data[r][c]){                     //If there's a white pixel
                if(background[r][c+1]){         //if at the border
                    r = 0;                      //forbids any more moves
                    c = 0;
                }
                else {                          //otherwise
                    data[r][c] = 0;                 //make pixel black
                    data[r][c + pixelmoveamount] = 1;   //and make the one to the right white
                }
            }
        }
    }
}

void rotate(uint8_t data[PIXELROWS][PIXELCOLUMNS]) { //rotates active blocks
    int r, c; //iterator variables for rows and columns
    int tetrominoCoord[2];
    int rotationMatrix[15][15]; //a subspace 
    int rotationDestination[15][15]; //that rotates
    for(r = PIXELROWS - 1; r >= 0; r--){        //row by row
        for(c = 0; c < PIXELCOLUMNS; c++){      //column by column
            if(data[r][c]){                      //find the tetr0mino
                tetrominoCoord[0] = r;
                tetrominoCoord[1] = c;
                r = 0;
                c = PIXELCOLUMNS;
            }
        }
    }
 
    //TODO blockspecific offset

    for(r = 0; r < 15; r++){
        for(c = 0; c < 15; c++){
            rotationMatrix[r][c] = foreground[tetrominoCoord[0]-7 + r][tetrominoCoord[1]- 7 + c]; //TODO real rotation
        }
    }

    for(r = 0; r < 15; r++){
        for(c = 0; c < 15; c++){
            rotationDestination[r][c] = rotationMatrix[14-c][r];
        }
    }

//Counter clockwise rotation :    destination[r][c] = matrix[c][x-r];    (where x is matrix size minus 1)
        //Clockwise : destination[r][c] = matrix[x-c][r];      (where x is matrix size minus 1)


    for(r = PIXELROWS - 1; r >= 0; r--){        //row by row
        for(c = 0; c < PIXELCOLUMNS; c++){      //column by column
            foreground[r][c] = 0;                  //clear foreground
        }
    }
    
    for (r = 0; r < 15; r++){
        for (c = tetrominoCoord[1]; c < tetrominoCoord[1] + 15; c++){
            foreground[tetrominoCoord[0]-7+r][tetrominoCoord[1]-7+c] = rotationDestination[r][c];
        }
    }
    rotationState = (rotationState + 1) % 4;

    delay(200);
    /**/
}


void showPiece(int row, int col, int pieceID, uint8_t target[PIXELROWS][PIXELCOLUMNS])
{
    int r, c;
    for (r = 0; r < 2 * 3; r++) {
        for (c = 0; c < 4 * 3; c++) {
            target[r + row][c + col] = tetrominos[pieceID][r / 3][c / 3];
        }
    }
}

void getNextPiece()
{
    nextPiece = ticks % 7;
    showPiece(NEXTAREAROW, NEXTAREACOLUMN, nextPiece, background);
}

void getPiece()
{
    showPiece(DROPAREAROW, DROPAREACOLUMN, nextPiece, foreground);
    rotationState = 0;
    tetrominoType = nextPiece;
}
