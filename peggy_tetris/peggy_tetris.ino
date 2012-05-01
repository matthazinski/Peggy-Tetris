#include <Peggy2.h>


// Don't include tetris.c, Arduino links it automatically

const int buttonPinLeft = 1;      // b2  left    24  ADC1
const int buttonPinRight = 4;     // b5  right   27  ADC4 
const int buttonPinRotate = 2;    // b3  down    25  ADC2
const int THRESHOLD = 512;

// Holds analog readings of button pins
int buttonRight;
int buttonLeft;
int buttonRotate;

// Whether the user was pushing down the button at the last check
boolean pushDownLeft;
boolean pushDownRight;
boolean pushDownRotate;

int fixed[24][10];   /* Blocks that are not moving */
int moving[24][10]; /* The moving block */
int combined[24][10]; /* What to display on the board */
int displayBoard[25][25]; /* Same as combined, but padded to take up the whole board */
int points = 0;


Peggy2 peggyFrame; /* Stores all pixels displayed on the Peggy */

char titleScreen[25][25] = {
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
}; 

char off[25][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

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


void setup() {

    //titleScreen[25][25]  /* "TETRIS \n START" */
    //peggyFrame.Peggy_HardwareInit();
    //peggyFrame.Peggy_Clear();
    peggyFrame.HardwareInit();
    peggyFrame.Clear();
    setFrameFromBoard(titleScreen);
    //pinMode(buttonPinLeft, INPUT);
    //pinMode(buttonPinRight, INPUT);
    //pinMode(buttonPinRotate, INPUT);
    buttonLeft = 0;
    buttonRight = 0;
    buttonRotate = 0;
    //Serial.begin(9600);
}


void loop() {
    unsigned long int tmp = millis();
    pushDownLeft = false;
    pushDownRight = false;
    pushDownRotate = false;
    //Serial.print("Left: ");
    //Serial.println(buttonLeft);   
      
    // Display title until user input
    setFrameFromBoard(titleScreen);    
    while((!pushDownLeft) && (!pushDownRight) && (!pushDownRotate)) {
      setFrameFromBoard(titleScreen);
      getUserInput();
    }    
    
    
    // Set-up the tetris game
    clearArray(moving);
    clearArray(fixed);
    clearArray(combined);
    for (int i = 0; i < 25; i++) {
      for (int j = 0; j < 25; j++) {
        displayBoard[i][j] = 0;
      }
    }
    
    setFrameFromBoard(displayBoard);
    unsigned long int nextClock = millis() + 2000;
    boolean gamePlaying = true;
    
    // Loop through until the user loses
    while (gamePlaying) {
      // Check to see if 
      if (abs(millis() - nextClock) < 20) {
        setRandomTile();
        mergeBoard();
        setFrameFromBoard(displayBoard);
        nextClock = nextClock + 2000;
      }
    }


    
    
    // Display end sequence
    
    

//    while(millis()<=tmp+2000){
//      setFrameFromBoard(off);
//    }
//    while(millis()<=tmp+4000){
//      setFrameFromBoard(titleScreen);
//    }
   
        
    
    // Wait for user input
    // Play a game of tetris
    // Display high score
    // Wait for user input
}


/* ---------------------------------------------------------
   ARDUINO HELPER METHODS 
   --------------------------------------------------------- */
void setFrameFromBoard(char board[25][25]) {
        
    /* This takes the board[][] parameter (which must be a 25x25 array) and
     * draws it on the Peggy display */
    //peggyFrame.Peggy_Clear();
    peggyFrame.Clear();
    for (int i = 0; i <= 24; i++) {
        for (int j = 0; j <= 24; j++) {
            //peggyFrame.Peggy_WritePoint(i, j, board[i][j]);
            peggyFrame.WritePoint(i, j, board[j][i]);
        }
    }  
    //peggyFrame.Peggy_RefreshAll(1);
    peggyFrame.RefreshAll(1);  
}

void setFrameFromBoard(int board[25][25]) {
    peggyFrame.Clear();
    for (int i = 0; i <= 24; i++) {
      for (int j = 0; j <= 24; j++) {
        if (board[i][j]) {
          peggyFrame.WritePoint(i, j, 15);
        }
        else {
          peggyFrame.WritePoint(i, j, 0);
        }
      }
    }
}

void getUserInput() {
    buttonLeft = analogRead(buttonPinLeft);
    buttonRight = analogRead(buttonPinRight);
    buttonRotate = analogRead(buttonPinRotate);

    if (buttonLeft < THRESHOLD) {
      pushDownLeft = true;
    }
    else{
      pushDownLeft = false;
    }

    if (buttonRight < THRESHOLD) {
      pushDownRight = true;
    }
    else {
      pushDownRight = false;
    }

    if (buttonRotate < THRESHOLD) {
      pushDownRotate = true;
    }
    else {
      pushDownRotate = false;
    }
}


  
  
  /* ---------------------------------------------------------
   ACTUAL TETRIS METHODS 
   --------------------------------------------------------- */
   
/* Zeros out a 24 x 10 2D array */
void clearArray(int array[24][10]) {
  int i, j;
  for (i = 0; i < 24; i++) {
    for (j = 0; j < 10; j++) {
      array[i][j] = 0;
    }
  }
}


/* Add a random tile aligned to the top 4 rows of the moving array */
void setRandomTile() {
  Tetromino tile;
  int tileNum = rand() % 7;
  switch(tileNum) {
  case 0: 
    tile = I; 
    break;
  case 1: 
    tile = L; 
    break;
  case 2: 
    tile = J; 
    break;
  case 3: 
    tile = S; 
    break;
  case 4: 
    tile = Z; 
    break;
  case 5: 
    tile = O; 
    break;
  case 6: 
    tile = T; 
    break;
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
  return;
}



void mergeBoard() {
  int i;
  int j;
  for (i = 0; i < 24; i++) {
    for (j = 0; j < 10; j++) {
      combined[i][j] = (fixed[i][j] || moving[i][j]);
      displayBoard[i][j] = combined[i][j];
    }
  }
}

void moveLeft() {
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

void moveRight() {
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

void rotate() {
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
