#include <Peggy2.h>


// Don't include tetris.c, Arduino links it automatically
const int buttonPinLeft = 1;      // b2  left    24  ADC1
const int buttonPinRight = 4;     // b5  right   27  ADC4 
const int buttonPinRotate = 2;    // b3  down    25  ADC2
int buttonRight;
int buttonLeft;
int buttonRotate;
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
    buttonLeft = analogRead(buttonPinLeft);
    buttonRight = analogRead(buttonPinRight);
    buttonRotate = analogRead(buttonPinRotate);
    
    unsigned long int tmp = millis();
   
    //Serial.print("Left: ");
    //Serial.println(buttonLeft);   
    
    
    if(buttonLeft < 500) {
      setFrameFromBoard(off);
    }
    
    if(buttonLeft >= 500) {
      setFrameFromBoard(titleScreen);
    }
    

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
