// Code for Arduino Mega
// Swaraj Singh
// 5th April, 2022

// Pins for 8 relay modules
#define relay1 41
#define relay2 40
#define relay3 45
#define relay4 44
#define relay5 35
#define relay6 34
#define relay7 30
#define relay8 31

// Pins for PWM to plain DC converter
#define pwmc1 2
#define pwmc2 4
#define pwmc3 6
#define pwmc4 9

// Pins for Bluetooth module
#define miso 50
#define mosi 51
#define sck 52

#include <SPI.h>      //SPI library for communicate with the nRF24L01+
#include "RF24.h"     //The main library of the nRF24L01+

//Define packet for the direction (X axis and Y axis)
int data[3];
int p[4];
bool send_v = true;
bool solenoid_bool[4];

//Define object from RF24 library - 9 and 10 are a digital pin 
//numbers to which signals CE and CSN are connected
RF24 radio(7,8);

//Create a pipe addresses for the communicate
const uint64_t pipe = 0xE8E8F0F0E1LL;
const int p_size = 4;
void setup(){
  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate            
  radio.openReadingPipe(1, pipe);   //Sets address of transmitter
  radio.startListening();    
  pinMode(pwmc1, OUTPUT);
  pinMode(pwmc2, OUTPUT);
  pinMode(pwmc3, OUTPUT);
  pinMode(pwmc4, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT); 
  pinMode(relay3, OUTPUT); 
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, HIGH);
  }

void loop(){
  if (radio.available()){
    radio.read(data, sizeof(data));
    if (send_v == true){
      Serial.print(data[0]);
      Serial.print('\n');
      Serial.print(data[1]);
      Serial.print('\n');
      Serial.print(data[2]);
      Serial.print('\n');
      send_v = false;
      }
    }
  if (send_v == false){
    if (Serial.available()){  
      p[0] = Serial.parseInt();
      p[1] = Serial.parseInt();
      p[2] = Serial.parseInt();
      p[3] = Serial.parseInt();
      solenoid_bool[0] = bool(Serial.parseInt());
      solenoid_bool[1] = bool(Serial.parseInt());
      solenoid_bool[2] = bool(Serial.parseInt());
      solenoid_bool[3] = bool(Serial.parseInt());
      press_reg(p, p_size);
      solenoid_valve(solenoid_bool);
      send_v = true;
      }
    }
  
  }

void send_solenoid_bool(int p[4]){
  bool sol[4];
  if (p[0] > 0) {
    sol[0] = true;
    }
  else {
    sol[0] = false;
    }
  if (p[1] > 0) {
    sol[1] = true;
    }
  else {
    sol[1] = false;
    }
  if (p[2] > 0) {
    sol[2] = true;
    }
  else {
    sol[2] = false;
    }
  if (p[3] > 0) {
    sol[3] = true;
    }
  else {
    sol[3] = false;
    }
  solenoid_valve(sol);
  }

void press_reg(int PWM[], int p_size){
  analogWrite(pwmc1, PWM[0]);
  analogWrite(pwmc2, PWM[1]);
  analogWrite(pwmc3, PWM[2]);
  analogWrite(pwmc4, PWM[3]); 
  }
  
void solenoid_valve(bool solenoid[4]){
  if (solenoid[0] == true){
    digitalWrite(relay1,LOW);  
    digitalWrite(relay2,HIGH);
    }
  else{
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,LOW);
    }
  if (solenoid[1] == true){
    digitalWrite(relay3,LOW);  
    digitalWrite(relay4,HIGH);
    }
  else{
    digitalWrite(relay3,HIGH);
    digitalWrite(relay4,LOW);
    }
  if (solenoid[2] == true){
    digitalWrite(relay5,LOW);  
    digitalWrite(relay6,HIGH);
    }
  else{
    digitalWrite(relay5,HIGH);
    digitalWrite(relay6,LOW);
    }
  if (solenoid[3] == true){
    digitalWrite(relay7,LOW);  
    digitalWrite(relay8,HIGH);
    }
  else{
    digitalWrite(relay7,HIGH);
    digitalWrite(relay8,LOW);
    }
  }
