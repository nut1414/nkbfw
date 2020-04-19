//Make sure to install all the library before uploading code.
//nut1414
#include <EEPROM.h>
#include <FastLED.h>
#include <Keyboard.h>
#include <Bounce2.h>

/*configuration*/

//#define HASLED 
#define LEDCHIPSET WS2812   //see FastLED list of supported chipset
#define LEDCLORDER GRB
//#define LIGHTLEDONBOOT
#define LEDPIN 16
#define LEDCOUNT 0
#define TURNOFFINBUILTLED

//#define STARTSERIAL
#define KEYCOUNT 4

/*set your key matrix here*/
#define COLKEYMATRIX 4
#define ROWKEYMATRIX 1

/*default pin of the switch*/
const uint8_t colpin[COLKEYMATRIX]=
  {
    9,8,10,16
  };
const uint8_t rowpin[ROWKEYMATRIX]=
  {
    NULL
  };

/*default key 
change your key binding here*/
uint8_t key[COLKEYMATRIX][ROWKEYMATRIX],defaultkey[COLKEYMATRIX][ROWKEYMATRIX]=
  {
    'z','x','c','v'
  };


//////////////////////////////////////////



Bounce button[KEYCOUNT];
#ifdef HASLED 
CRGB leds[LEDCOUNT];
#endif
String serialstr;
char parsechar[24],cmd[5];
int i,j,count,crow,ccol;
uint8_t ckey;
void setup(){
  
 //begin keyboard
Keyboard.begin();
Serial.begin(9600);


 
//attach bounce
int buttoncount;
 for (int k = 0; k < ROWKEYMATRIX ; k++) 
 {
  pinMode(rowpin[k],OUTPUT);
  for (int l = 0; l < COLKEYMATRIX; l++) 
  {
    key[l][k] = defaultkey[l][k];
    button[buttoncount] = Bounce();                                     
    button[buttoncount].attach(colpin[l], INPUT_PULLUP); 
    button[buttoncount].interval(5);
    buttoncount++;
  }
 }

  
 //option to disable inbuilt led
 #ifdef TURNOFFINBUILTLED
  pinMode(LED_BUILTIN, INPUT);
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
 #endif

 
 //init led
 #ifdef HASLED 
  FastLED.addLeds<LEDCHIPSET,LEDPIN,LEDCLORDER>(leds,LEDCOUNT);
  
  #ifdef LIGHTLEDONBOOT
 
  for (int k = 0;k<LEDCOUNT;k++)
   {
   //change led color here
    leds[k]=CRGB::White;
    FastLED.show();
   }
  #endif
 
 #endif
 



}


//parsing the serial input
void serialParser(String input)
{
  //converting serial.tostring to char array
  input.toCharArray(parsechar,20);
  
  //scan for cmd
  sscanf(parsechar,"%s %d %d %x",cmd, &ccol, &crow, &ckey);
  
  
  if(strcmp(cmd,"CK")==0)
  {
   key[ccol][crow] = ckey;
   Serial.println(key[ccol][crow]);
   
  }else if(strcmp(cmd,"DK")==0)
  {
    for (int k = 0; k < ROWKEYMATRIX ; k++) 
      {
        
        for (int l = 0; l < COLKEYMATRIX; l++) 
          {
            
            key[l][k] = defaultkey[l][k];
            
          }
      }
  }else
  {
    Serial.println("INVALID");  
  }
  
  
}

void loop() {
 count = 0;
 for (j = 0; j < ROWKEYMATRIX; j++) 
 {
  digitalWrite(rowpin[j],HIGH);
  
  for(i = 0; i < COLKEYMATRIX; i++)
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
 
 while (Serial.available() > 0) 
 {
    serialstr = Serial.readString();
  
    serialParser(serialstr);
 }

 
}
