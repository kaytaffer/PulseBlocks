/* blockmovement.c
functions related to manipulating blocks
For copyright and licensing, see file COPYING */

#include "pulseblockheader.h" /*project declarations */

int falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to a lesser position each time function is called 
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
    tetrominoCoord[0]++;
    return freefall;
}

void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    uint8_t moved = 0;
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
                    moved = pixelmoveamount;
                }
            }
        }
    }
    tetrominoCoord[1] -= moved;
}

void rightMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    uint8_t moved = 0;
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
                    moved = pixelmoveamount;
                }
            }
        }
    }
    tetrominoCoord[1] += moved;
}

void rotate(uint8_t data[PIXELROWS][PIXELCOLUMNS]) { //rotates active block clockwise
    int r, c; //iterator variables for rows and columns
    uint8_t rotationMatrix[15][15]; //a subspace 
    uint8_t rotationDestination[15][15]; //that rotates
    uint8_t checkRotOK = 1;
    while ((tetrominoCoord[0] % 3) != 2){ //enables falling pixel-by-pixel with maintained block alignment
        falling(foreground, 1);
    }
    for(r = 0; r < 15; r++){        //row by row
        for(c = 0; c < 15; c++){    //column by column
            rotationMatrix[r][c] = data[tetrominoCoord[0]-7 + r][tetrominoCoord[1]- 7 + c]; //takes a snapshout around the block
        }
    } 
    for(r = 0; r < 15; r++){            //row by row
        for(c = 0; c < 15; c++){        //column by column
            rotationDestination[r][c] = rotationMatrix[14-c][r];     //rotates the block
            if(background[tetrominoCoord[0]-7+r][tetrominoCoord[1]-7+c])  //Checks target area
                checkRotOK = 0;                 //Don't rotate out of the world
        }
    }
    //Counter clockwise rotation :    destination[r][c] = matrix[c][x-r];    (where x is matrix size minus 1)
    //Clockwise : destination[r][c] = matrix[x-c][r];      (where x is matrix size minus 1)
    if (checkRotOK){
        clearScreen(foreground);  //clear data (foreground probably)
        for (r = 0; r < 15; r++){       //row by row
            for (c = 0; c < 15; c++){   //column by column
                data[tetrominoCoord[0]-7+r][tetrominoCoord[1]-7+c] = rotationDestination[r][c]; //Write rotaded matrix to data (foreground probably)
            }
        }
    }
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
    tetrominoCoord[0] = DROPCENTERPIXELROW; //resets the tetraminotracker
    tetrominoCoord[1] = DROPCENTERPIXELCOLUMN;
    score++;
}
