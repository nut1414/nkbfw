/*configuration*/


//#define HASLED
#define LEDCHIPSET WS2812   //see FastLED list of supported chipset
#define LEDCLORDER GRB
#define LEDPIN 2
#define LEDCOUNT 1  //NEVER under any circumstance set led count to 0, this will crash the board and you have to ground the reset pin in order to upload any code again. (has led only)
#define DEFAULTR 255
#define DEFAULTG 192
#define DEFAULTB 203
#define TURNOFFINBUILTLED

#define NAME "Keypad"

#define EEPROMSAVE
#define EEPROMLK 100 //eeprom location for storing key byte
#define EEPROMCHK 1023 //eeprom location for checking first time write
#define EEPROMLED -90 //eeprom led offset

/*set your key matrix here*/
#define COLKEYMATRIX 4
#define ROWKEYMATRIX 1
#define KEYCOUNT 4

/*default pin of the switch*/
const uint8_t colpin[COLKEYMATRIX]=
  {
    9,8,10,16
  };
const uint8_t rowpin[ROWKEYMATRIX]=
  {
    NULL
  };

/*
default key change your key binding here
if using modifier enter with out bracket 
example: "{KEY_LEFT_SHIFT,'x','c'}"

*/
uint8_t key[ROWKEYMATRIX][COLKEYMATRIX];
uint8_t defaultkey[ROWKEYMATRIX][COLKEYMATRIX]={
   {'z','x','c','v'}
};
