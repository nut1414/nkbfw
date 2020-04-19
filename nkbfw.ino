//Make sure to install all the library before uploading code.
//nut1414
#include <EEPROM.h>
#include <FastLED.h>
#include <Keyboard.h>
#include <Bounce2.h>

//configuration
#define HASLED FALSE
#define LEDCHIPSET WS2812 //see FastLED list of supported chipset
#define LEDCLORDER GRB
#define LIGHTLEDONBOOT FALSE
#define LEDPIN 16
#define LEDCOUNT 0
#define TURNONINBUILTLED FALSE

#define STARTSERIAL TRUE
#define KEYCOUNT 4

//set your key matrix here
#define XKEYMATRIX 4
#define YKEYMATRIX 1

//default pin of the switch
const uint8_t colpin[XKEYMATRIX]=
  {
    9,8,10,16
  };
const uint8_t rowpin[YKEYMATRIX]=
  {
    NULL
  };

//default key 
//change your key binding here
uint8_t defaultkey[XKEYMATRIX][YKEYMATRIX],key[XKEYMATRIX][YKEYMATRIX]=
  {
    'z','x','c','v'
  };


//////////////////////////////////////////

Bounce button[KEYCOUNT];
#if HASLED == TRUE
CRGB leds[LEDCOUNT];
#endif

int i,j,count;

void setup(){
  
 //begin keyboard
 Keyboard.begin();
 #if STARTSERIAL == TRUE
  Serial.begin(9600);
 #endif

  
 //option to disable inbuilt led
 #if TURNONINBUILTLED == FALSE
  pinMode(LED_BUILTIN, INPUT);
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
 #endif

 
 //init led
 #if HASLED == TRUE
  FastLED.addLeds<LEDCHIPSET,LEDPIN,LEDCLORDER>(leds,LEDCOUNT);
  
  #if LIGHTLEDONBOOT == TRUE
 
  for (int k = 0;k<LEDCOUNT;k++)
   {
   //change led color here
    leds[k]=CRGB::White;
    FastLED.show();
   }
  #endif
 
 #endif
 


int buttoncount;
 //attach bounce
 for (int k = 0; k < YKEYMATRIX ; k++) 
 {
  pinMode(rowpin[k],OUTPUT);
  for (int l = 0; l < XKEYMATRIX; l++) 
  {
    button[buttoncount] = Bounce();                                     
    button[buttoncount].attach(colpin[l], INPUT_PULLUP); 
    button[buttoncount].interval(5);
    buttoncount++;
  }
 }



//no use of the serial as of yet but definetly planned


}

void loop() {
 count = 0;
 for (j = 0; j < YKEYMATRIX; j++) 
 {
  digitalWrite(rowpin[j],HIGH);
  for(i = 0; i < XKEYMATRIX; i++)
    {
      button[count].update();
      
      if (button[count].fell()){
       Keyboard.press(key[i][j]);
     }
      if (button[count].rose()){
      Keyboard.release(key[i][j]);
     }
     count++;
    }
   digitalWrite(rowpin[j],LOW);
 }
}
