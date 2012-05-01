/*
 * This is older code used for testing a tetris library for Arduino in GCC.
 * There are a few bugs I haven't bothered to fix because all code was just
 * moved into peggy_tetris.ino. This is probably not a file you want.
*/
#include <stdio.h>   /* IO for debugging */
#include <stdlib.h> /* Used for memory allocation, may be unnecessary */

void clearArray(int[24][10]);
void printArray(int*, int, int);
int* mergeBoard(int[24][10], int[24][10]);
int checkBoard();
void setRandomTile();
void clock();
void fixMoving();
void moveLeft();
void moveRight();
void rotate();

/*
 * Blocks become fixed when any point of the moving block is touching the
 * boundary of the fixed block.
 */

int fixed [24][10];   /* Blocks that are not moving */
int moving [24][10]; /* The moving block */
int points = 0;

/* Defines the default position of tetrominos in the moving array */
typedef struct {
    int a_row, a_col;
    int b_row, b_col;
    int c_row, c_col;
    int d_row, d_col;
} Tetromino;


Tetromino I = {3, 3,  3, 4,  3, 5,  3, 6};
Tetromino L = {1, 4,  2, 4,  3, 4,  3, 5};
Tetromino J = {1, 5,  2, 5,  3, 5,  3, 4};
Tetromino S = {2, 4,  2, 5,  3, 4,  3, 3};
Tetromino Z = {3, 4,  3, 5,  2, 4,  2, 3};
Tetromino O = {2, 4,  2, 5,  3, 4,  3, 5};
Tetromino T = {3, 4,  3, 5,  2, 5,  3, 6};



/*
 * At the moment, the main() function is primarily used for testing and
 * debugging. 
 */
int main() {
    clearArray(moving);
    clearArray(fixed);

    srand(0);   /* Initialize random seed */
    

    /* Debugging info */
    int j;
    for (j = 0; j < 10; j++) {
        fixed[10][j] = 1;
    }

    printf("Initial board:\n");
    printArray(&fixed, 24, 10);
    printf("Checking array\n");
    checkBoard();
    printArray(&fixed, 24, 10);
    printf("Points: %d \n", points);
    
    
    /* More debugging info */
    printf("Printing moving board:\n");
    printArray(&moving, 24, 10);
    printf("Adding random tile:\n");

    int k;
    for (k = 0; k < 7; k++) {
        setRandomTile();
        printArray(&moving, 24, 10);
        printf("\n\n\n");
        clearArray(moving);
    }

	/*  trying to move left */
	setRandomTile();
	printArray(&moving,24,10);
	printf("\n\n\n");
	moveLeft();
	printArray(&moving,24,10);
	
	/*move right*/
	printf("\n\n\n");
	moveRight();
	printArray(&moving,24,10);
	

    getchar();
    return 0;
}


/* Zeros out a 24 x 10 2D array */
void clearArray(int array[24][10]) {
    int i, j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 10; j++) {
            array[i][j] = 0;
        }
    }
}



/* Prints an array of arbitrary size to stdout. This is used for debugging. */
void printArray(int* array, int height, int width) {
    int i, j;

    for (i = 0; i < height; i++) {
         
        for (j = 0; j < width; j++) {
            printf("%d ", *(array+i*width+j));
        }
        
        printf("\n");
    }
}

/* Add a random tile aligned to the top 4 rows of the moving array */
void setRandomTile() {
    Tetromino tile;
    int tileNum = rand() % 7;
    switch(tileNum) {
        case 0: tile = I; break;
        case 1: tile = L; break;
        case 2: tile = J; break;
        case 3: tile = S; break;
        case 4: tile = Z; break;
        case 5: tile = O; break;
        case 6: tile = T; break;
    }
    
    moving[tile.a_row][tile.a_col] = 1;
    moving[tile.b_row][tile.b_col] = 1;
    moving[tile.c_row][tile.c_col] = 1;
    moving[tile.d_row][tile.d_col] = 1;
}



/* Determines if game is lost, then shifts cells down and updates score */
int checkBoard() {
    /* 
     * Check to see if the user has lost the game (i.e. tiles are in the four
     * hidden rows)
     */
    int i;
    int j;
    int status = 0;
    for (i = 0; i < 4; i++) { /* Search the first four rows */
        for (j = 0; j < 10; j++) {
            if (fixed[i][j] == 1) {
                status =  1;  /* Lose game */
            }
        }
    }

    /* Check the fixed board for complete rows and remove them */
    int newBoard[24][10];
    int counter = 23;
    for (i = 23; i >= 0; i--) {
        int sum = 0;
        for (j = 0; j < 10; j++) {
            sum = sum + fixed[i][j];
        }

        if (sum == 10) {
            points = points + 100;  
        }
        else {
            for (j = 0; j < 10; j++) {
                newBoard[counter][j] = fixed[i][j];
            }
            counter--;
        }
    }
    
    for (i = counter; i >= 0; i--) {
        for (j = 0; j < 10; j++) {
            newBoard[counter][j] = 0;
        }
    }

    /* Move the new board back to the fixed board */
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 10; j++) {
            fixed[i][j] = newBoard[i][j];
        }
    }
    
    
    return status;
}


/*
 * This moves the moving board down by one row, and fixes the tiles whenever
 * they are touching the fixed board or occupying the bottom row.
 */
void clock() {

    /* Move moving down one row and replace with zeros */
    int i, j;
    for (i = 23; i > 0; i--) {
        for (j = 0; j < 10; j++) {
            moving[i][j] = moving[i-1][j];
        }
    }
    
    for (j = 0; j < 10; j++) {
        moving[0][j] = 0;
    }

    /* Move moving tiles to fixed if necessary */
    for (i = 0; i < 23; i++) {
        for (j = 0; j < 10; j++) {
            if (moving[i][j] == 1) {
                if (fixed[i+1][j] == 1) {
                    fixMoving();
                }
            }
        }
    }

    for (j = 0; j < 10; j++) {
        if (moving[23][j] == 1) {
            fixMoving();
        }
    }
    
}

void fixMoving() {
    int i,j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 10; j++) {
            if (moving[i][j] == 1) {    
                fixed[i][j] == 1;
                moving[i][j] == 0;
            }
        }
    }
}



int* mergeBoard(int fixed[24][10], int moving[24][10]) {
    int board[24][10];
    int i;
    int j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 10; j++) {
            board[i][j] = (fixed[i][j] || moving[i][j]);
        }
    }

    return &board;
}

void moveLeft()
{
	int i, j;
	/*check whether moving will hit a wall or piece*/
	int isValidMove=1;
	for(i=0; i<24; i++) {
		for(j=0; j<10; j++) {
			if(moving[i][j]==1) {
				if(fixed[i][j-1]==1)
					isValidMove=0;
				else if(j-1==-1)
					isValidMove=0;
			}
		}
	}
	/* if it can move, move the piece*/
	if(isValidMove==1)
		for(i=0; i<24; i++) {
			for(j=0; j<10; j++) {
				if(moving[i][j]==1) {
					moving[i][j]=0;
					moving[i][j-1]=1;
				}
			}
		}
		
	return;
}

void moveRight()
{
	int i, j;
	/*check whether moving will hit a wall or piece*/
	int isValidMove=1;
	
	for(i=0; i<24; i++) {
		for(j=0; j<10; j++) {
			if(moving[i][j]==1) {
				if(fixed[i][j+1]==1)
					isValidMove=0;
				else if(j+1==10)
					isValidMove=0;
			}
		}
	}

	/* if it can move, move the piece*/
	if(isValidMove==1)
		for(i=0; i<24; i++) {
			for(j=9; j>=0; j--) {
				if(moving[i][j]==1) {
					moving[i][j]=0;
					moving[i][j+1]=1;
				}
			}
		}
		
	return;
}

void rotate()
{
        int i, j, validRotate=1, rotate=1, pointI, pointJ, Moving[24][10];
        for(i=0;i<24;i++){
        	for(j=0;j<10;j++)
      			Moving[i][j]=moving[i][j]; //Creates a temporary array for moving.
        }
        
        for(i=0;i<24;i++){
        	for(j=0;j<10;j++){
        		if(Moving[i][j]==1){ //The conditions must be met for the piece to rotate. 
        			if((Moving[i+1][j]==1||Moving[i-1][j]==1)&&(Moving[i][j+1]||Moving[i][j-1])){
        				if(Moving[i+2][j]==1||Moving[i][j+2]==1)
        					continue;
        				rotate=1;
        				pointI=i; //This sets the point around which it will rotate.
        				pointJ=j;
        				}
        			else if(Moving[i+1][j]==1&&Moving[i-1][j]==1){	
        				rotate=1;
        				pointI=i;
        				pointJ=j;
        				}
        			else if(Moving[i][j+1]==1&&Moving[i][j-1]==1){	
        				rotate=1;
        				pointI=i;
        				pointJ=j;
        				}
        		}
        	}
        	break;
        }
        
        i=pointI;
        j=pointJ;
        if(rotate==1){
        	int tempCross, tempDiag, tempLine;
        	tempCross=Moving[i-1][j];
        	tempDiag=Moving[i-1][j+1];
        	tempLine=Moving[i][j+2];
        	
        	Moving[i-1][j]=Moving[i][j-1];
        	Moving[i][j-1]=Moving[i+1][j]; //Rotates all the respective parts around.
        	Moving[i+1][j]=Moving[i][j+1];
        	Moving[i][j+1]=tempCross;
        	
        	Moving[i-1][j+1]=Moving[i-1][j-1];
        	Moving[i-1][j-1]=Moving[i+1][j-1];
        	Moving[i+1][j-1]=Moving[i+1][j+1];
        	Moving[i+1][j+1]=tempDiag;
        	
        	Moving[i+2][j]=Moving[i][j+2];
        	Moving[i][j+2]=tempLine;
        }
        
         for(i=0;i<24;i++){
                for(j=0;j<10;j++){
                        if(Moving[i][j]==1){
                if(Moving[i][j]==fixed[i][j]) //Checks if the rotate is valid.
                        validRotate=0;
						}
                }
        }
        
        if(validRotate==1){
        for(i=0;i<24;i++){
        	for(j=0;j<10;j++) //Sets the moving array to the temp array so it is turned.
      			moving[i][j]=Moving[i][j];
        }
        }
        
        return;
}
