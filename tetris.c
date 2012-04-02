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
    
int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; //board for tetris    
    
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

