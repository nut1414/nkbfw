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
//eeprom location for storing key byte
#define EEPROMLK 100
//eeprom location for checking first time write
#define EEPROMCHK 1023

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
int i,j,count,argi1,argi2,argi3;
bool firstc = false;
uint8_t argb1;

void setup(){
  
//begin keyboard
Keyboard.begin();
Serial.begin(9600);

//EEPROM writing default if have not written before

if(EEPROM.read(EEPROMCHK) == 255)
  {
    EEPROM.write(EEPROMCHK, 127);
    firstc=true;
  }



//attach bounce
int buttoncount;

 for (int k = 0; k < ROWKEYMATRIX ; k++) 
 {
  pinMode(rowpin[k],OUTPUT);
  for (int l = 0; l < COLKEYMATRIX; l++) 
  {
    
    button[buttoncount] = Bounce();                                     
    button[buttoncount].attach(colpin[l], INPUT_PULLUP); 
    button[buttoncount].interval(5);
    //do read/write eeproms
    //for the first boot
    if (firstc==true)
    {
      //if the key that is already been written isn't the same as the default, overwrite the key
      if (EEPROM.read(EEPROMLK+buttoncount)!=defaultkey[l][k])
      {
      EEPROM.write(EEPROMLK+buttoncount,defaultkey[l][k]);
      }
    }
    key[l][k] = EEPROM.read(EEPROMLK+buttoncount);
    buttoncount++;
  }
 }

firstc==false;
  
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
  sscanf(parsechar,"%s",cmd);
  
  
  if(strcmp(cmd,"CK")==0)
   {
   sscanf(parsechar,"%s %d %d %x",cmd,&argi1,&argi2,&argb1);
   //making sure to not setting unknown key loc
   if((argi1<COLKEYMATRIX)||(argi2<ROWKEYMATRIX))
   {
   key[argi1][argi2] = argb1;
   //Serial.println(key[argi1][argi2]);
   Serial.println("OK");
   }else Serial.println("INVALID");
  }else if(strcmp(cmd,"DK")==0)
  {
    for (int k = 0; k < ROWKEYMATRIX ; k++) 
      {
        
        for (int l = 0; l < COLKEYMATRIX; l++) 
          {
            
            key[l][k] = defaultkey[l][k];
            
          }
      }
      Serial.println("OK");
  }else if(strcmp(cmd,"SK")==0)
  {
    int b= 0;
   
    for (int k = 0; k < ROWKEYMATRIX ; k++) 
    {
     for (int l = 0; l < COLKEYMATRIX; l++) 
     {
      //if the key that is already been written isn't the same as the default, overwrite the key
      if (EEPROM.read(EEPROMLK+b)!=key[l][k])
      {
      EEPROM.write(EEPROMLK+b,key[l][k]);
      Serial.println("CHANGE");
      Serial.println(EEPROM.read(EEPROMLK+b));
      Serial.println("LOC");
      Serial.println(EEPROMLK+b);
      }
      b++;
     }
    
   } Serial.println("OK");
 }else Serial.println("INVALID");
   
  
  
  
  
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
