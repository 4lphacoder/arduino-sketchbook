//transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define leftYAxis A4
#define rightYAxis A6
#define rightXAxis A7
#define PB0 7
#define PB1 4

struct sendData {
 int pb0;
 int pb1;
 };


RF24 radio(9, 10); // CE, CSN
const byte address[12] = "03620802717";


void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


void loop() {
  sendData controller;
  controller.pb0 = digitalRead(PB0);
  controller.pb1 = digitalRead(PB1);
  Serial.print(controller.pb0);
  Serial.print("\t");
  Serial.println(controller.pb1);
  radio.write(&controller, sizeof(controller));
}
