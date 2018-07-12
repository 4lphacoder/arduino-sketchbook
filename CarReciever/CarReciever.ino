//Reciever
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN
const byte address[12] = "03620802717";

struct sendData {
 int pb0;
 int pb1;
 };
 
#define rightForward 4
#define leftForward 2
#define rightBackward 6
#define leftBackward 7
#define rightSpeedController 3
#define leftSpeedController 5


void forward()
{
  digitalWrite(leftForward,HIGH);
  digitalWrite(rightForward,HIGH);
}

void backward()
{
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightBackward,HIGH);
}

void left()
{
  digitalWrite(rightForward,HIGH);
  digitalWrite(leftBackward,HIGH);
}

void right()
{
   digitalWrite(leftForward,HIGH);
   digitalWrite(rightBackward,HIGH);
}


void moveStop()
{
  digitalWrite(leftForward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightBackward,LOW);
}


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  digitalWrite(leftSpeedController,HIGH);
  digitalWrite(rightSpeedController,HIGH);
  if(radio.available())
  {
    sendData controller;
    radio.read(&controller, sizeof(controller));
     Serial.print(controller.pb0);
     Serial.print("\t");
     Serial.println(controller.pb1);
 
    if(controller.pb0 == 1)
     {
       forward();
       delay(20);
       moveStop();
  }
     if(controller.pb1 == 1)
     {
       backward();
       delay(20);
       moveStop();
  }
   }
}
