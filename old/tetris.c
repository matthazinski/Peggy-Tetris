/*
 * This is not the file you want. It doesn't compile. Matt rewrote it and put
 * it in tetris2.c.
 */
#define BOARD_WIDTH     10
#define BOARD_HEIGHT    20

void fullRow(int[][]);
void rotateCW(int[][]);
void rotateCCW(int[][]);


int main() {

    
    srand(time(NULL));
    int random = rand()%7;
    int block [][];

    switch(random) {

        case 0: block = a;
        case 1: block = b;
        case 2: block = c;
        case 3: block = d;
        case 4: block = e;
        case 5: block = f;
        case 6: default: block = g;
    }
    
    /* I */
    int a [4][4] = {{0,0,0,0},
                   {1,1,1,1}.
                   {0,0,0,0},
                   {0,0,0,0}};

    /* O */
    int b [4][4] = {{0,0,0,0},
                   {0,1,1,0},
                   {0,1,1,0},
                   {0,0,0,0}};

    /* Z */
    int c [4][4] = {{0,0,0,0},
                   {0,1,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    /* S */
    int d [4][4] = {{0,0,0,0},
                   {0,0,1,1},
                   {0,1,1,0},
                   {0,0,0,0}};

    /* L */
    int e [4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    /* J */
    int f [4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,1,1,0},
                   {0,0,0,0}};

    /* T */
    int g [4][4] = {{0,0,1,0},
                   {0,1,1,1},
                   {0,0,0,0},
                   {0,0,0,0}};
    
    int mBoard [BOARD_HEIGHT][BOARD_WIDTH]; //board for tetris    

    return 0;
}


//if a row is full, moves all rows down 1 position... I hope...
void fullRow(int mBoard[][]) {
    int i = 19;

    while ( 1 < i )   {
            int k = 0;
            //if row is full
            if (mBoard[i][BOARD_WIDTH] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1})  {
                for (k = 0; k < (19 - i); k++ )  {
                //set full row to row above it, etc.
                    mBoard[i-k][BOARD_WIDTH] = mBoard [i-1-k][BOARD_WIDTH];
                }
                //reset top row to compensate for row we deleted
                mBoard[19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
            }
            i--;
    }
    //special case for top row, reset to zeroes
    if (field[0][10] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1})
        field[0][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}
    
void mBoard::GameOver(){
    int i;
    for(i=0; i<200; i++) {  //for when the area is over or equal to 200, game starts over. 10x20
        if(area[i]!=EMPTY) {
            area[i]|=BREAK;
        }
    }
}
    
    
    

//rotates a piece clockwise
void rotateCW(int tetromino[4][4])
{
    int temp1,temp2,temp3;
    temp1 = tetromino[1][1];
    temp2 = tetromino[1][2];
    temp3 = tetromino[2][2];
    tetromino[1][1] = tetromino[2][1];
    tetromino[1][2] = temp1;
    tetromino[2][2] = temp2;
    tetromino[2][1] = temp3;
    for(int i=0;i<4;i++)
    {
        temp1 = tetromino[0][i];
        temp2 = tetromino[i][3];
        temp3 = tetromino[3][3-i];
        tetromino[0][i] = tetromino[3-i][0];
        tetromino[i][3] = temp1;
        tetromino[3][3-i] = temp2;
        tetromino[3-i][0] = temp3;
    }
    return;
}

// Likely unnecessary function
//rotates a piece counter clockwise
void rotateCCW(int tetromino[4][4])
{
    int temp1,temp2,temp3;
    temp3 = tetromino[1][1];
    temp2 = tetromino[2][1];
    temp1 = tetromino[2][2];
    tetromino[1][1] = tetromino[1][2];
    tetromino[2][1] = temp3;
    tetromino[2][2] = temp2;
    tetromino[1][2] = temp1;
    for(int i=0;i<4;i++)
    {
        temp3 = tetromino[0][i];
        temp2 = tetromino[i][3];
        temp1 = tetromino[3][3-i];
        tetromino[3][3-i] = tetromino[3-i][0];
        tetromino[i][3] = temp1;
        tetromino[0][i] = temp2;
        tetromino[3-i][0] = temp3;
    }
    return;
}



