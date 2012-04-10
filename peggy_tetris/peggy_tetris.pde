#include <Peggy2.h>


// Don't include tetris.c, Arduino links it automatically

Peggy2 peggyFrame; /* Stores all pixels displayed on the Peggy */
/*char titleScreen[25][25] = {
        {0, 15, 15, 15, 0, 15, 15, 15, 0, 15, 15, 15, 0, 15, 15, 0, 0, 15, 15, 15, 0, 0, 15, 15, 0},
        {0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 15, 0, 0, 15, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 0},
        {0, 0, 15, 0, 0, 15, 15, 0, 0, 0, 15, 0, 0, 15, 15, 0, 0, 0, 15, 0, 0, 0, 15, 0, 0},
        {0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 15, 0, 0, 15, 0, 15, 0, 0, 15, 0, 0, 0, 0, 15, 0},
        {0, 0, 15, 0, 0, 15, 15, 15, 0, 0, 15, 0, 0, 15, 0, 15, 0, 15, 15, 15, 0, 15, 15, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0, 0},
        {0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 0, 0},
        {0, 0, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0},
        {0, 0, 15, 15, 0, 0, 0, 0, 15, 15, 15, 0, 0, 0, 15, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 15, 15, 0, 15, 15, 15, 0, 0, 15, 0, 0, 15, 15, 0, 0, 15, 15, 15, 0, 0, 0},
        {0, 0, 0, 15, 0, 0, 0, 0, 15, 0, 0, 15, 0, 15, 0, 15, 0, 15, 0, 0, 15, 0, 0, 0, 0},
        {0, 0, 0, 0, 15, 0, 0, 0, 15, 0, 0, 15, 15, 15, 0, 15, 15, 0, 0, 0, 15, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 15, 0, 15, 0, 15, 0, 0, 15, 0, 0, 0, 0},
        {0, 0, 0, 15, 15, 0, 0, 0, 15, 0, 0, 15, 0, 15, 0, 15, 0, 15, 0, 0, 15, 0, 0, 0, 0}
    }; */

void setup() {

    //titleScreen[25][25] = /* "TETRIS \n START" */


    peggyFrame.HardwareInit();
    peggyFrame.Clear();
    //setFrameFromBoard(titleScreen);
}


void loop() {
    //setFrameFromBoard(titleScreen);
    // Wait for user input
    // Play a game of tetris
    // Display high score
    // Wait for user input
}


void setFrameFromBoard(char board[25][25]) {
    /* This takes the board[][] parameter (which must be a 25x25 array) and
     * draws
     *        it on the Peggy display */
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            peggyFrame.WritePoint(i, j, board[i][j]);
        }
    }  
    peggyFrame.RefreshAll(1);
}

