/* Note: for indents, use 4-character spaces, NOT tabs. */

#include <Peggy2.h>
#define BOARD_WIDTH     10
#define BOARD_HEIGHT    20

Peggy2 frame; // Stores all pixels displayed on the Peggy
// I'm assuming we have a Peggy2.


void setup() {
    // This function is called when the Arduino starts up
    frame.HardwareInit();
    frame.Clear();
}


void loop() {
    
    
    srand(time(NULL));
    int random = rand()%7;
    int[][] block;

    switch(random){
    
    case 0:
        block = a;
    case 1:
        block = b;
    case 2:
        block = c;
    case 3:
        block = d;
    case 4:
        block = e;
    case 5:
        block = f;
    case 6:
        block = g;
    }
    
    /*  line */
    int a[4][4] = {{0, 0, 0, 0},
           {1, 1, 1, 1}.
           {0, 0, 0, 0},
           {0, 0, 0, 0}};

    /* square */
    int b[4][4] = {{0,0,0,0},
           {0,1,1,0},
           {0,1,1,0},
           {0,0,0,0}};

    /* Z */
    int c[4][4] = {{0,0,0,0},
                   {0,1,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    /* S */
    int d[4][4] = {{0,0,0,0},
                   {0,0,1,1},
                   {0,1,1,0},
                   {0,0,0,0}};

    /* L */
    int e[4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    /* reverse L */
    int f[4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,1,1,0},
                   {0,0,0,0}};

    /* T */
    int g[4][4] = {{0,0,1,0},
                   {0,1,1,1},
                   {0,0,0,0},
                   {0,0,0,0}};
    
    int mBoard [BOARD_HEIGHT][BOARD_WIDTH]; //board for tetris    


}


//if a row is full, moves all rows down 1 position... I hope...
void fullRow(int mBoard[][]) {
    int i = 19;

    while ( 1 < i )   {
            int k = 0;
            //if row is full
            if (Board[i][BOARD_WIDTH] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1})  {
                for (k = 0; k < (19 - i); k++ )  {
                //set full row to row above it, etc.
                    mBoard[i-k][BOARD_WIDTH] = mBoard [i-1-k][BOARD_WIDTH];
                }
            }
            i--;
    }
    //special case for top row, reset to zeroes
    if (field[0][10] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1})
        field[0][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}
    
bool Board::IsGameOver() {
    //The game will be over when the first line has blocks in it
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) return true; //checks if the first row of board is "filled"
    }
 
    return false;
}    
    
    
void setFrameFromBoard(int board[][]) {
    /* This takes the board[][] parameter (which must be a 25x25 array) and draws
       it on the Peggy display */
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            frame.WritePoint(i, j, board[i][j]);
        }
    }  
    frame.RefreshAll(1);
}
//rotates a peice clockwise
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


//rotates a peice counter clockwise
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





