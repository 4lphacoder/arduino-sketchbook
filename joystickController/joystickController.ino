//Joystick Controller

#include<SPI.h>
#include<RF24.h>
#include<nRF24L01.h>


#define pushButton0 7
#define pushButton1 4
#define pushButton2 8
#define pushButton3 A1
#define pushButton4 A2
#define pushButton5 A0
#define pushButton6 A3
#define pushButton7 5
#define pushButton8 6
#define pushButton9 3
#define pushButton10 2
#define rightJoystickY A6
#define rightJoystickX A7
#define leftJoystickY A4
#define leftJoystickX A5

//******************************


//****Radio Initialisation********

RF24 radio(9,10);
const uint64_t address = 03620802717;

//*******Pins Declarations********



//********Structure of transmitting Data***********

struct txData { 
  boolean pB0;
  boolean pB1;
  boolean pB2;  
  boolean pB3;
  boolean pB4;
  boolean pB5;
  boolean pB6;
  boolean pB7;
  boolean pB8;
  boolean pB9;
  boolean pB10;
  
  byte rightJStickX;
  byte rightJStickY;
  byte leftJStickX;
  byte leftJStickY;
};

//*************************************************


void setup()
  {
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.stopListening();
    pinMode(pushButton0,INPUT);
    pinMode(pushButton1,INPUT);
    pinMode(pushButton2,INPUT);
    pinMode(pushButton3,INPUT);
    pinMode(pushButton4,INPUT);
    pinMode(pushButton5,INPUT);
    pinMode(pushButton6,INPUT);
    pinMode(pushButton7,INPUT);
    pinMode(pushButton8,INPUT);
    pinMode(pushButton9,INPUT);
    pinMode(pushButton10,INPUT);
    
    //Serial.println("\t\t\t\t\t\t\t\t\t\t\tTransmiiting Values\n**************************************************************************************************************************************************************************************************");
  }
  
//****Function to take mapped input from User*********  
  
byte input(uint8_t key)
  {
    byte tmp;
    tmp = map(analogRead(key),131,1022,0,100);
    return tmp;
  }

//***************************************************
  
  
void loop()
  {
    txData controls;
    
    controls.pB0 = digitalRead(pushButton0);  
    controls.pB1 = digitalRead(pushButton1);
    controls.pB2 = digitalRead(pushButton2);
    controls.pB3 = digitalRead(pushButton3);
    controls.pB4 = digitalRead(pushButton4);
    controls.pB5 = digitalRead(pushButton5);
    controls.pB6 = digitalRead(pushButton6);
    controls.pB7 = digitalRead(pushButton7);
    controls.pB8 = digitalRead(pushButton8);
    controls.pB9 = digitalRead(pushButton9);
    controls.pB10 = digitalRead(pushButton10);
    controls.rightJStickX = input(rightJoystickX);
    controls.rightJStickY = input(rightJoystickY);
    controls.leftJStickX = input(leftJoystickX);
    controls.leftJStickY = input(leftJoystickY);
    
    //*****************Transmitting Values**************************
    /*
        Serial.print("Left JoyStick X : ");
        Serial.print(controls.leftJStickX);
        Serial.print("\t\tLeft JoyStick Y: ");
        Serial.print(controls.leftJStickY);
        Serial.print("\t\tRight JoyStick X : ");
        Serial.print(controls.rightJStickX);
        Serial.print("\t\tRight JoyStick Y: ");
        Serial.println(controls.rightJStickY);
      */  
     //*******************************************************
    radio.write(&controls,sizeof(controls));
  }
