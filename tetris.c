#define BOARD_WIDTH 	10
#define BOARD_HEIGHT	20

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
    
    // line
    int a[4][4] = {{0, 0, 0, 0},
		   {1, 1, 1, 1}.
		   {0, 0, 0, 0},
		   {0, 0, 0, 0}};

    // square
    int b[4][4] = {{0,0,0,0},
		   {0,1,1,0},
		   {0,1,1,0},
		   {0,0,0,0}};

    // Z
    int c[4][4] = {{0,0,0,0},
                   {0,1,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    // S
    int d[4][4] = {{0,0,0,0},
                   {0,0,1,1},
                   {0,1,1,0},
                   {0,0,0,0}};

    // L
    int e[4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,0,1,1},
                   {0,0,0,0}};

    // reverse L
    int f[4][4] = {{0,0,1,0},
                   {0,0,1,0},
                   {0,1,1,0},
                   {0,0,0,0}};

    // T
    int g[4][4] = {{0,0,1,0},
                   {0,1,1,1},
                   {0,0,0,0},
                   {0,0,0,0}};
    
int mBoard [BOARD_HEIGHT][BOARD_WIDTH]; //board for tetris    


//if a row is full, moves all rows down 1 position... I hope...
void fullRow(int mBoard[][])

{
int i = 19;

	while ( 1 < i )
		{
			int k = 0;
				//if row is full
				if mBoard[i][BOARD_WIDTH] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
					{
						for (k = 0; k < (19 - i); k++ )	
						{
						//set full row to row above it, etc.
						mBoard[i-k][BOARD_WIDTH] = mBoard [i-1-k][BOARD_WIDTH];
						}
					}
			i--;
		}
	//special case for top row, reset to zeroes
	if field[0][10] == {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		field[0][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}
    
bool Board::IsGameOver()
{
    //The game will be over when the first line has blocks in it
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (mBoard[i][0] == POS_FILLED) return true; //checks if the first row of board is "filled"
    }
 
    return false;
}    
    
    
    



}

