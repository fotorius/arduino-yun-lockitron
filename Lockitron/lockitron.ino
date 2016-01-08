/*
  Lockitron
  Simple Arduino Yún door access application usin Lockitron

  Documentation: https://github.com/devalfrz/arduino-yun-lockitron  

  This example code is in the public domain.

  created 7 Jan 2016
  by Alfredo Rius
 */

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

#define OPEN 0
#define CLOSE 1

YunServer server;

/*
*     THIS IS YOUR PASSWORD
*/
const char password[] = "arduino";



const int buttonPin = 12;
const int boardLed =  13;
const int redLed =    11;
const int greenLed =  10;
const int pwm = 3;
const int motorA = 5;
const int motorB = 6;
const int swA1 = 4;
const int swA2 = 8;

int locked = OPEN;

int lock(int state){
      digitalWrite(boardLed, HIGH);
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, LOW);
      digitalWrite(motorA, state);
      digitalWrite(motorB, !state);
      if(state){
        while(digitalRead(swA2));
        while(!digitalRead(swA1));
      }
      else{
        while(digitalRead(swA1));
        while(!digitalRead(swA2));
      }
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
      digitalWrite(boardLed, LOW);
      digitalWrite(greenLed, state);
      digitalWrite(redLed, !state);
      return state;
}

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  pinMode(boardLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(pwm, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  
  digitalWrite(redLed, !locked);
  digitalWrite(greenLed, locked);
  digitalWrite(pwm,HIGH);
  //analogWrite(pwm, 128); //DEBUG
}
 
void loop() {
  YunClient client = server.accept();
 
  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "status"){
      client.print(locked);
    }
    else if (command == "lock") {
      locked = lock(CLOSE);
      client.print(locked);
    }
    else if (command == password) {
      locked = lock(OPEN);
      client.print(locked);
    }
    else{ // Error
      client.print("2");
    }
    client.stop();
  }

  if (digitalRead(buttonPin)) {
      /*
      // DEBUG
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, HIGH);
      while(digitalRead(buttonPin));
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
      */
      locked = lock(!locked);
  }
  delay(50);
}
