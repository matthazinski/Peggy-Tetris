void loop() {
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	srand(time(NULL));
    int random = rand()%7;
    
    switch(random){}
    
    case 0:
    	char block='a';
    case 1:
    	char block='b';
    case 2:
    	char block='c';
    case 3:
    	char block='d';
    case 4:
    	char block='e';
    case 5:
    	char block='f';
    case 6:
    	char block='g';
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

