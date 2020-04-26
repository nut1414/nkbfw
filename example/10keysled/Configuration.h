/*configuration*/


#define HASLED
#define LEDCHIPSET WS2812   //see FastLED list of supported chipset
#define LEDCLORDER GRB
#define LEDPIN 16
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
#define COLKEYMATRIX 10
#define ROWKEYMATRIX 1
#define KEYCOUNT 10

/*default pin of the switch*/
const uint8_t colpin[COLKEYMATRIX]=
  {
    2,3,A0,4,5,6,7,8,9,10
  };
const uint8_t rowpin[ROWKEYMATRIX]=
  {
    NULL
  };

/*
default key change your key binding here
if using modifier enter with out bracket 
example: "{KEY_LEFT_SHIFT,'x','c','v'}"

*/
uint8_t key[ROWKEYMATRIX][COLKEYMATRIX];
uint8_t defaultkey[ROWKEYMATRIX][COLKEYMATRIX]={
   {'1','2','3','4','5','6','7','8','9','0'}
};
