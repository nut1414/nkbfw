#include <EEPROM.h>
#include <Keyboard.h>
#include <Bounce2.h>


//key count
#define KEYCOUNT 10

//default key
#define K1 'A'
#define K2 'B'
#define K3 'C'
#define K4 'D'
#define K5 'E'
#define K6 'F'
#define K7 'G'
#define K8 'H'
#define K9 'I'
#define K10 'J'

//default pin of the switch
#define P1 2
#define P2 3
#define P3 4
#define P4 5
#define P5 6
#define P6 7
#define P7 8
#define P8 9
#define P9 10
#define P10 11


byte pin[KEYCOUNT]=
{     }

bool test;

void setup() {
 //check if never been started before
 if(EEPROM.read(1023)== 255);
 {
  
 }
  

//start the serial
Serial.begin(9600);
pinMode(1,INPUT);
}

void loop() {
test = digitalRead(1);
if(test==true){
  Serial.print("yes");
  }
}
