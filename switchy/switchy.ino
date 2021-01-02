#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define LIGHT_THRESHOLD 430
#define UPDATE_TIMEOUT 60000

// Motor control pins
int in1 = 9;
int in2 = 10;

// Photoresistor pin
int photoPin = A5;

int lightVal = 0;

void setup() {
  #if DEBUG == 1
    Serial.begin(9600);
  #endif
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(photoPin, INPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void goForward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  #if DEBUG == 1
    Serial.print("Pin 1: ");
    Serial.println(HIGH);
    Serial.print("Pin 2: ");
    Serial.println(LOW);
  #endif
}

void stopMotor(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  #if DEBUG == 1
    Serial.print("Pin 1: ");
    Serial.println(LOW);
    Serial.print("Pin 2: ");
    Serial.println(LOW);
  #endif
}

void switchOnBulb(){
    #if DEBUG == 1
      Serial.println("Start motion");
    #endif
    goForward();
    delay(500);
    stopMotor();
    delay(500);
    goBackward();
    delay(500);
    stopMotor();
}

void goBackward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  #if DEBUG == 1
    Serial.print("Pin 1: ");
    Serial.println(LOW);
    Serial.print("Pin 2: ");
    Serial.println(HIGH);
  #endif
}

void loop() {
  lightVal = analogRead(photoPin);
  #if DEBUG == 1
    Serial.println(lightVal);
  #endif

  // Check the light value and if lower than the threshold
  // power on the light bulb 
  if(lightVal <= LIGHT_THRESHOLD){
    switchOnBulb();
  }
  
  delay(UPDATE_TIMEOUT);
  #if DEBUG == 1
    Serial.println("Start again");
  #endif
}
