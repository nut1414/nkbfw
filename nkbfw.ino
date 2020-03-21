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

byte pin[KEYCOUNT]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10};

//bool test;
int i;
Bounce button[KEYCOUNT];

void setup() {
 //check if never been started before
 /*
 if(EEPROM.read(1023)!= 1);
 {
  
 }
 */
 //attach bounce
  for (i = 0; i < KEYCOUNT; i++) {
    button[i] = Bounce();                                     
    button[i].attach(pin[i], INPUT_PULLUP); 
    button[i].interval(5);
  }

//start the serial
Serial.begin(9600);
pinMode(1,INPUT);
}

void loop() {
  /*
test = digitalRead(1);
if(test==true){
  Serial.print("yes");
  }*/
for(i=0;i<KEYCOUNT;i++)
  {
  button[i].update();
  }

  
  if (button[0].fell()){
    Keyboard.press(K1);
  }
  if (button[0].rose()){
    Keyboard.release(K1);
  }
  
if (button[1].fell()){
    Keyboard.press(K2);
  }
  if (button[1].rose()){
    Keyboard.release(K2);
  }
  
if (button[2].fell()){
    Keyboard.press(K3);
  }
  if (button[2].rose()){
    Keyboard.release(K3);
  }
  
if (button[3].fell()){
    Keyboard.press(K4);
  }
  if (button[3].rose()){
    Keyboard.release(K4);
  }

if (button[4].fell()){
    Keyboard.press(K5);
  }
  if (button[4].rose()){
    Keyboard.release(K5);
  }

if (button[5].fell()){
    Keyboard.press(K6);
  }
  if (button[5].rose()){
    Keyboard.release(K6);
  }

if (button[6].fell()){
    Keyboard.press(K7);
  }
  if (button[6].rose()){
    Keyboard.release(K7);
  }

if (button[7].fell()){
    Keyboard.press(K8);
  }
  if (button[7].rose()){
    Keyboard.release(K8);
  }

if (button[8].fell()){
    Keyboard.press(K9);
  }
  if (button[8].rose()){
    Keyboard.release(K9);
  }

if (button[9].fell()){
    Keyboard.press(K10);
  }
  if (button[9].rose()){
    Keyboard.release(K10);
  }

  
}
