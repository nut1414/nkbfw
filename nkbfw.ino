//Make sure to install all the library before uploading code.
//nut1414
#include <EEPROM.h>
#include <FastLED.h>
#include <Keyboard.h>
#include <Bounce2.h>

//configuration
#define TURNONLED FALSE
#define TURNONINBUILTLED FALSE
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
//making things tidier                  
char key[KEYCOUNT]={K1,K2,K3,K4,K5,K6,K7,K8,K9,K10};
    
//bool test;
int i;
int j;
Bounce button[KEYCOUNT];

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
Serial.begin(9600);
pinMode(1,INPUT);
}

void loop() {
for(i=0;i<KEYCOUNT;i++)
  {
  button[i].update();
  if (button[i].fell()){
    Keyboard.press(key[i]);

  }
  if (button[i].rose()){
    Keyboard.release(key[i]);
    
  
  }
  }
 
}
