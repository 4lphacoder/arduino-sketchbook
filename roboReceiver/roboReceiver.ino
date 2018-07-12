//Robo Car

#include<SPI.h>
#include<RF24.h>
#include<nRF24L01.h>


//******Pins Declarations********************

#define leftSpeedController 3
#define rightSpeedController 5
#define rightForward 4
#define leftForward 2
#define rightBackward 6
#define leftBackward 7
#define trig A0
#define echo A1
#define servoController 8

#define leftIR A7
#define rightIR A6

#define senseDelay 10
#define lTrigger 200
#define rTrigger 200

//***************Radio Initialisation***********

RF24 radio(9,10); // CE, CSN
const uint64_t address = 03620802717;
int flag = 0;


struct rxData { 
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


void moveForward()
  {
    digitalWrite(rightForward,HIGH);
    digitalWrite(leftForward,HIGH);
  }
  
void moveBackward()
  {
    digitalWrite(rightBackward,HIGH);
    digitalWrite(leftBackward,HIGH);
  }

void moveStop()
  {
    digitalWrite(rightForward,LOW);
    digitalWrite(leftForward,LOW);
    digitalWrite(rightBackward,LOW);
    digitalWrite(leftBackward,LOW);
  }
  
void moveLeft()
   {
    digitalWrite(rightForward,HIGH);
  }
  
void moveRight()
  {
    digitalWrite(leftForward,HIGH);
  }
  
void rotateLeft()
  {
    digitalWrite(leftBackward,HIGH);
    digitalWrite(rightForward,HIGH);
  }
  
void rotateRight()
  {
    digitalWrite(leftForward,HIGH);
    digitalWrite(rightBackward,HIGH);
  }

void setup()
  {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1,address);
    radio.startListening();
    
    
  }
 

void radioCar()
  {
       rxData controls;
       radio.read(&controls,sizeof(controls));
        
       Serial.print(controls.leftJStickX);
       Serial.print("\t");
       Serial.print(controls.leftJStickY);
       Serial.print("\t");
       Serial.print(controls.rightJStickX);
       Serial.print("\t");
       Serial.print(controls.rightJStickY);
       Serial.print("\t");
       Serial.print(controls.pB0);
       Serial.print("\t");
       Serial.print(controls.pB1);
       Serial.print("\t");
       Serial.print(controls.pB5);
       Serial.println("\t");
   
       
        
       //*****throttle******************************************************************
        
       analogWrite(leftSpeedController,map(controls.leftJStickY,1,100,255,50));
       analogWrite(rightSpeedController,map(controls.leftJStickY,1,100,255,50));
 
       //********************************************************************************
        
       //*************Moving Forward*****************************************************
      if(controls.pB0 == 1)
        {
         moveForward();
         delay(20);
         moveStop(); 
        }
        
       //**********************************************************************************
       
       
       //****************Moving Backward****************************************************
       if(controls.pB1 == 1)
        {
         moveBackward();
         delay(20);
         moveStop(); 
        }
        
        //************************************************************************************
        
        
        //*************Moving Left************************************************************
        if(controls.rightJStickX <= 50 && controls.rightJStickX >= 0)
        {
          if(controls.rightJStickX <= 50 && controls.rightJStickX >= 0)
             {
               analogWrite(leftSpeedController,map(controls.rightJStickX,0,50,255,50)); 
               analogWrite(rightSpeedController,map(controls.rightJStickX,0,50,255,50));
               moveLeft();
               delay(20);
               moveStop();
             }
        }
        
     //********************************************************************************************
        
    //*************************Moving Right**********************************************************
 
        if(controls.rightJStickX >= 54 && controls.rightJStickX <= 100)
        {
         
         if(controls.rightJStickX >= 54 && controls.rightJStickX <= 100)
             {
               analogWrite(leftSpeedController,map(controls.rightJStickX,54,100,50,255)); 
               analogWrite(rightSpeedController,map(controls.rightJStickX,54,100,50,255));
               moveRight();
               delay(20);
               moveStop();
             }
           }
   //****************************************************************************************************  
   
   
   //*************************Rotating Left****************************************************
          if(controls.leftJStickX <= 50 && controls.rightJStickX >= 4)
             {
               analogWrite(leftSpeedController,map(controls.leftJStickX,50,4,50,100)); 
               analogWrite(rightSpeedController,map(controls.leftJStickX,50,4,50,100));
               rotateLeft();
               delay(20);
               moveStop();
             }                    

   //****************************************************************************************************** 
   
   
   
   //*************************Rotating Right****************************************************
          if(controls.leftJStickX >= 54 && controls.rightJStickX <= 100)
             {
               analogWrite(leftSpeedController,map(controls.leftJStickX,54,100,50,100)); 
               analogWrite(rightSpeedController,map(controls.leftJStickX,54,100,50,100));
               rotateRight();
               delay(20);
               moveStop();
             }                    

   //****************************************************************************************************** 
   
   
  }


    
void loop()
  { 
  
  //Radio Controlled Robot
 
   if(radio.available())
     {
       radioCar();
        }
     
 }
