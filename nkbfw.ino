//Make sure to install all the library before uploading code.
//nut1414
#include <EEPROM.h>
#include <FastLED.h>
#include <Keyboard.h>
#include <Bounce2.h>

//configuration
#define TURNONLED FALSE //OR TRUE (in capital letter)
#define TURNONINBUILTLED FALSE

#define STARTSERIAL FALSE
#define KEYCOUNT 10


//default key 
//change your key binding here
#define K1 '1'
#define K2 '2'
#define K3 '3'
#define K4 '4'
#define K5 '5'
#define K6 '6'
#define K7 '7'
#define K8 '8'
#define K9 '9'
#define K10 '0'


//default pin of the switch
#define P1 2
#define P2 3
#define P3 A0
#define P4 4
#define P5 5
#define P6 6
#define P7 7
#define P8 8
#define P9 9
#define P10 10

CRGB leds[1];
byte pin[KEYCOUNT]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10};
//making things tidier, not                  
//char fKEYCOUNT]={K1,K2,K3,K4,K5,K6,K7,K8,K9,K10};
    
//bool test;
int i;
int j;
Bounce button[KEYCOUNT];
void setup(){
//option to disable inbuilt led
 #if TURNONINBUILTLED == FALSE
 pinMode(LED_BUILTIN_TX,INPUT);
 pinMode(LED_BUILTIN_RX,INPUT);
 #endif
 //init led
 
 FastLED.addLeds<WS2812,16,GRB>(leds,1);
 leds[1]=CRGB::Black;
 FastLED.show();
 #if TURNONLED == TRUE
 //change led color here
 leds[1]=CRGB::Pink;
 FastLED.show();
 #endif
 //check if never been started before
 //planned feature

 /*
 if(EEPROM.read(1023)!= 1);
 {
  
 }                     
 */ 
 //begin keyboard
 Keyboard.begin();
 //attach bounce
  for (i = 0; i < KEYCOUNT; i++) {
    button[i] = Bounce();                                     
    button[i].attach(pin[i], INPUT_PULLUP); 
    button[i].interval(5);
  }

//start the serial
#if STARTSERIAL == TRUE
Serial.begin(9600);
#endif

}

void loop() {
for(i=0;i<KEYCOUNT;i++)
  {
  button[i].update();
 
  } 
  if (button[0].fell()){
    Keyboard.press(K1);
  }
  if (button[0].rose()){
    Keyboard.release(K2);
    
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
