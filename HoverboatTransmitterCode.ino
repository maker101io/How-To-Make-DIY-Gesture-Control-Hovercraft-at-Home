#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"                     //the library which helps us to control the radio modem

//define the input pins
int Xaxis = A0;
int Yaxis = A1;

//define variable values
int xValue;
int yValue;

int data[1];

RF24 radio(8,10); //8 and 10 are a digital pin numbers to which signals CE and CSN are connected.
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.


void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem.
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
}

void loop(){
  
  //Send X-axis data
  xValue = analogRead(Xaxis);
  xValue = map(xValue, 0, 1023, 0, 10);
  data[0] = xValue;
  radio.write(data, 1); 
  
  //Send Y-axis data
  yValue = analogRead(Yaxis);
  yValue = map(yValue, 0, 1023, 11, 20);
  data[0] = yValue;
  radio.write(data, 1);
}
