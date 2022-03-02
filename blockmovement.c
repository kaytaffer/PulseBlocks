/* blockmovement.c
functions related to manipulating blocks
For copyright and licensing, see file COPYING */

#include "pulseblockheader.h" /*project declarations */

int falling(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
    for(r = PIXELROWS - 1; r >= 0; r--){        //row by row
        for(c = 0; c < PIXELCOLUMNS; c++){      //column by column
            if(data[r][c] == 1){                //If there's a white pixel
                data[r][c] = 0;                 //make pixel black
                data[r + pixelmoveamount][c] = 1;   //and make the one underneath white
                if (background[r + pixelmoveamount + 1][c]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void leftMove(uint8_t data[PIXELROWS][PIXELCOLUMNS], int pixelmoveamount){ /* Makes all elements in data array move to one lesser position each time function is called 
int screenTransition; //associated to fallingLineRepeat */ 
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
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
    int r = PIXELROWS; //iterator variable for rows
    int c = PIXELCOLUMNS; //iterator variable for columns
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

    //TODO implement
}

// this should be deleted later
void showRandomPiece(uint8_t target[PIXELROWS][PIXELCOLUMNS], uint8_t row, uint8_t column)
{
    int r, c;
    for (r = 0; r < 2 * 3; r++) {
        for (c = 0; c < 4 * 3; c++) {
            target[r + row][c + column] = tetrominos[ticks % 7][r / 3][c / 3];
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
    showPiece(DROPAREAROW, DROPAREACOLUMN, nextPiece, background);
    
}

//what to do when piece dropped
void pieceDropped()
{
    getPiece();
    getNextPiece();
}
