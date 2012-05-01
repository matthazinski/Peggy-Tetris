#include <Peggy2.h>


// Don't include tetris.c, Arduino links it automatically

const int buttonPinLeft = 1;      // b2  left    24  ADC1
const int buttonPinRight = 4;     // b5  right   27  ADC4 
const int buttonPinRotate = 3;    // b3  down    25  ADC2  
const int buttonPinDrop = 2;
const int THRESHOLD = 512;
const int DELAY = 100;

// Holds analog readings of button pins
int buttonRight;
int buttonLeft;
int buttonRotate;
int buttonDrop;

// Whether the user was pushing down the button at the last check
boolean pushDownLeft;
boolean pushDownRight;
boolean pushDownRotate;
boolean pushDownDrop;

char fixed[24][10] = {0};   /* Blocks that are not moving */
char moving[24][10] = {0}; /* The moving block */
char combined[24][10] = {0}; /* What to display on the board */
char displayBoard[25][25] = {0}; /* Same as combined, but padded to take up the whole board */
int points = 0;
boolean gamePlaying;
unsigned long int nextClock;
unsigned long int nextInput;

char tileType;
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
                  {0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
Tetromino L = {1, 4,  3, 4,  2, 4,  3, 5};
Tetromino J = {1, 5,  3, 5,  2, 5,  3, 4};
Tetromino S = {2, 5,  2, 4,  3, 4,  3, 3};
Tetromino Z = {3, 5,  3, 4,  2, 4,  2, 3};
Tetromino O = {2, 4,  2, 5,  3, 4,  3, 5};
Tetromino T = {3, 4,  3, 5,  2, 5,  3, 6};


void setup() {
    peggyFrame.Peggy_HardwareInit();
    peggyFrame.Peggy_Clear();
    buttonLeft = 0;
    buttonRight = 0;
    buttonRotate = 0;
    buttonDrop = 0;
    pushDownLeft = false;
    pushDownRight = false;
    pushDownRotate = false;
    pushDownDrop = false;
    /*
    while(!pushDownLeft && !pushDownRight && !pushDownRotate) {
      setFrameFromBoard(titleScreen);
      getUserInput();
    }
    */
    gamePlaying = true;
    setRandomTile();
    nextClock = millis();
    nextInput = millis();
    
}


void loop() {
    
    // Loop through until the user loses
    if(nextInput < millis() && gamePlaying) {
      // Handle user input events
    getUserInput();
      if(pushDownLeft) {
        moveLeft();
      }
      else if(pushDownRight) {
        moveRight();
      }
      else if(pushDownRotate) {
        rotate();
      } 
      else if(pushDownDrop) {
        drop();
      }
      
      nextInput = millis() + DELAY;
      
      
    }
      
      if(nextClock < millis() && gamePlaying) {
        mergeBoard();
        clock();
  
        if(checkBoard()) { //Detect loses
          mergeBoard();
          gamePlaying = false;
        }
        nextClock = millis() + 2 * DELAY;
      }
    
      setFrameFromBoard(displayBoard); 
    // TODO add end sequence
}


/* ---------------------------------------------------------
   ARDUINO HELPER METHODS 
   --------------------------------------------------------- */
void setFrameFromBoard(char board[25][25]) {
        
    /* This takes the board[][] parameter (which must be a 25x25 array) and
     * draws it on the Peggy display */
    peggyFrame.Peggy_Clear();
    for (int i = 0; i <= 24; i++) {
        for (int j = 0; j <= 24; j++) {
            peggyFrame.Peggy_WritePoint(i, j, board[j][i]);
        }
    }  
    peggyFrame.Peggy_RefreshAll(1);  
}

void setFrameFromIntBoard(int board[25][25]) {
    peggyFrame.Peggy_Clear();
    for (int i = 0; i <= 24; i++) {
      for (int j = 0; j <= 24; j++) {
        if (board[i][j]) {
          peggyFrame.Peggy_WritePoint(j, i, 15);
        }
        else {
          peggyFrame.Peggy_WritePoint(j, i, 0);
        }
      }
    }
    peggyFrame.Peggy_RefreshAll(1);
}

void getUserInput() {
    buttonLeft = analogRead(buttonPinLeft);
    buttonRight = analogRead(buttonPinRight);
    buttonRotate = analogRead(buttonPinRotate);
    buttonDrop = analogRead(buttonPinDrop);
    if (buttonDrop < THRESHOLD) {
      pushDownDrop = true;
    }
    else{
      pushDownDrop = false;
    }
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
    tileType = 'I';
    break;
  case 1: 
    tile = L; 
    tileType = 'L';
    break;
  case 2: 
    tile = J; 
    tileType = 'J';
    break;
  case 3: 
    tile = S; 
    tileType = 'S';
    break;
  case 4: 
    tile = Z; 
    tileType = 'Z';
    break;
  case 5: 
    tile = O; 
    tileType = 'O';
    break;
  case 6: 
    tile = T; 
    tileType = 'T';
    break;
  }

  moving[tile.a_row][tile.a_col] = 1;
  moving[tile.b_row][tile.b_col] = 2;
  moving[tile.c_row][tile.c_col] = 1;
  moving[tile.d_row][tile.d_col] = 1;
}



/* Determines if game is lost, then shifts cells down and updates score */
int checkBoard() {
  /* 
   * Check to see if the user has lost the game (i.e. tiles are in the four
   * hidden rows)
   */
  int status = 0;
  for (int i = 0; i < 4; i++) { /* Search the first four rows */
    for (int j = 0; j < 10; j++) {
      if (fixed[i][j]) {
        status =  1;  /* Lose game */
      }
    }
  }



  /* Check the fixed board for complete rows and remove them */
  int row=24, sum = 0;
  while(row>=0){
    sum = 0;
    for(int i=0;i<10;i++)
      if(fixed[row][i])
        sum++;
    if(sum==10){
      for(int i=row;i>=0;i--)
        for(int j=0;j<10;j++)
          fixed[i][j]=fixed[i-1][j];
      for(int i=0;i<10;i++)
        fixed[0][i]=0;
    }
    
   row--;
  }


  for (int i  = 0; i < 24; i++) {
    int sum = 0;
    for (int j = 0; j < 10; j++) {
      if(fixed[i][j]) sum+=1;
    }
    
    if(sum == 10) {
      for (int j = 0; j < 10; j++) {
        fixed[i][j] = 0;  
      }
    }
  }
      
//  /* Move the new board back to the fixed board */
//  for (int i = 0; i < 24; i++) {
//    for (int j = 0; j < 10; j++) {
//      fixed[i][j] = newBoard[i][j];
//    }
//  }

// TODO test this function


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
  boolean needsFixing = false;
  for (i = 0; i < 23; i++) {
    for (j = 0; j < 10; j++) {
      if (moving[i][j]) {
        if (fixed[i+1][j]) {
          needsFixing = true;
        }
      }
    }
  }

    
  for (j = 0; j < 10; j++) {
    if (moving[23][j]) {
      needsFixing = true;
    }
  }
  
  if (needsFixing) {
    fixMoving();
  }

}

void fixMoving() {
  boolean changed = false;
  int i,j;
  for (i = 0; i < 24; i++) {
    for (j = 0; j < 10; j++) {
      if (moving[i][j]) {    
        fixed[i][j] = 1;
        moving[i][j] = 0;
        changed = true;
      }
    }
  }
  if(changed) {
    setRandomTile();
  }
  return;
}



void mergeBoard() {
  int i;
  int j;
  for (i = 0; i < 24; i++) {
    for (j = 0; j < 10; j++) {
      //combined[i][j] = fixed[i][j] || moving[i][j];
      displayBoard[i][j] = (fixed[i][j] || moving[i][j]) ? 15 : 0;
    }
  }
}

void moveLeft() {
  int i, j;
  /*check whether moving will hit a wall or piece*/
  int isValidMove=1;
  for(i=0; i<24; i++) {
    for(j=0; j<10; j++) {
      if(moving[i][j]) {
        if(fixed[i][j-1])
          isValidMove=0;
        else if(j-1==-1)
          isValidMove=0;
      }
    }
  }
  /* if it can move, move the piece*/
  if(isValidMove)
    for(i=0; i<24; i++) {
      for(j=0; j<10; j++) {
        if(moving[i][j]==1) {
          moving[i][j]=0;
          moving[i][j-1]=1;
        }
        else if(moving[i][j]==2) {
          moving[i][j]=0;
          moving[i][j-1]=2;
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
      if(moving[i][j]) {
        if(fixed[i][j+1])
          isValidMove=0;
        else if(j+1==10)
          isValidMove=0;
      }
    }
  }

  /* if it can move, move the piece*/
  if(isValidMove)
    for(i=0; i<24; i++) {
      for(j=9; j>=0; j--) {
        if(moving[i][j]==1) {
          moving[i][j]=0;
          moving[i][j+1]=1;
        }
        else if(moving[i][j]==2) {
          moving[i][j]=0;
          moving[i][j+1]=2;
        }
      }
    }

  return;
}




void rotate() {
  //makes temporary moving
  int x, y, i, j;
  char tempMoving[24][10];
  for(i=0;i<24;i++)
    for(j=0;j<10;j++)
      tempMoving[i][j] = moving[i][j];

  
  //finds the position of the second detected piece and rotates around it
  for(i=0;i<24;i++)
    for(j=0;j<10;j++) {
      if(tempMoving[i][j]==2){
        y=i;
        x=j;
      }
    }
  int corner_x = x-2;
  int corner_y = y-2;
  
  //rotates it like a 5x5 matrix
  for(i=0;i<5;i++)
    for(j=0;j<5;j++){
      if(moving[corner_y+j][corner_x+4-i]){
        if(corner_y+i>23)return;
        if(corner_x+j>9)return;
        if(corner_x+j<0)return;
        if(fixed[corner_y+i][corner_x+j])return;
      }
      tempMoving[corner_y+i][corner_x+j] = moving[corner_y+j][corner_x+4-i];   
    }
    
  for(i=0;i<24;i++)
    for(j=0;j<10;j++)
      moving[i][j] = tempMoving[i][j];
  
}

void drop() {
  bool cont=1;
  int tempFixed[24][10];
  for(int i=0;i<24;i++){
    for(int j=0;j<10;j++){
      tempFixed[i][j]=fixed[i][j];}}
  while(cont){
    
    for(int i=0;i<24;i++){
      for(int j=0;j<10;j++){
        if(!(tempFixed[i][j]==fixed[i][j])){
          cont=0;  }}}
    mergeBoard();
    clock();
  }
}
  
