/* 
 * Working tetris code. Do not push commits to this file unless it compiles in
 * GCC using C89.
 */

#include <stdio.h>   /* IO for debugging */
#include <stdlib.h> /* Used for memory allocation, may be unncecessary */

void printArray(int*, int, int);
int* mergeBoard(int[24][10], int[24][10]);
int checkBoard();

/*
 * Blocks become fixed when any point of the moving block is touching the
 * boundary of the fixed block.
 */

int fixed [24][10];   /* Blocks that are not moving */
int moving [24][10]; /* The moving block */
int points = 0;


/*
 * At the moment, the main() function is primarily used for testing and
 * debugging. 
 */
int main() {
    int i, j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 10; j++) {
            fixed[i][j] = 0;
        }
    }

    for (j = 0; j < 10; j++) {
        fixed[10][j] = 1;
    }

    printf("Initial board:\n");
    printArray(&fixed, 24, 10);
    printf("Checking array\n");
    checkBoard();
    printArray(&fixed, 24, 10);
    printf("Points: %d \n", points);
    
    return 0;
}

/* Prints an array of arbitrary size to stdout. This is used for debugging. */
void printArray(int* array, int height, int width) {
    int i;
    int j;

    for (i = 0; i < height; i++) {
        
        for (j = 0; j < width; j++) {
            printf("%d ", *(array+i*width+j));
        }
        
        printf("\n");
    }
}


/*
 * Determines if game is lost, then shifts cells down and updates the
 * display
 */
int checkBoard() {
    /* 
     * Check to see if the user has lost the game (i.e. tiles are in the four
     * hidden rows
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
            printf("Points for %d: %d\n", i, points);
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
        for (j = 0; j < 23; j++) {
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

    /* Move moving down one row */

    /* Move moving tiles to fixed if necessary */

    /* Merge board for display */

    /* Check board */
    
    /* Merge board for display */

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
