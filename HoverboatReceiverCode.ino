#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem (nRF24L)

//define our L298N control pins
//Define enable pins of the Motors
const int enbA = 3;
const int enbB = 9;
//Motor A
const int RightMotorForward = 2;
const int RightMotorBackward = 5;
//Motor B
const int LeftMotorForward = 6;
const int LeftMotorBackward = 7;

//Define variable for the motors speeds
//I have defined a variable for each of the two motors 
//This way you can synchronize the rotation speed difference between the two motors

RF24 radio(8,10);     /*This object represents a modem connected to the Arduino. 
                      Arguments 8 and 10 are a digital pin numbers to which signals 
                      CE and CSN are connected.*/

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino.

int data[1];


void setup(){
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  radio.begin();                    //it activates the modem.
  radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data.
  radio.startListening();           //enable receiving data via modem
  }

void loop(){
  if(radio.available()){
    radio.read(data, 1);
    
    if(data[0] < 11 && data[0] > 6){
    // This is backward
    digitalWrite(enbA, HIGH);
    digitalWrite(enbB, HIGH);
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, HIGH);
    }
    
    if(data[0] > -1 && data[0] < 4){
    // This is forward
    digitalWrite(enbA, HIGH);
    digitalWrite(enbB, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    }
    
    if (data[0] == 5){
    // Stop Motors
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
    }
    
    if(data[0] < 21 && data[0] > 16){
    digitalWrite(enbA, HIGH);
    digitalWrite(enbB, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, HIGH);
    }
    
    if(data[0] > 10 && data[0] < 14){
    digitalWrite(enbA, HIGH);
    digitalWrite(enbB, HIGH);
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    }
    
    if(data[0] == 15){
    digitalWrite(enbA, HIGH);
    digitalWrite(enbB, HIGH);
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
    }
  }
}
