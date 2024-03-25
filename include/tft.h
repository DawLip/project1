#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include "Fast_ST7789.h"

#define TFT_DC    2     
#define TFT_RST   15    
#define TFT_CS    -1    

extern Fast_ST7789 tft;

extern void init_tft();
extern void t_print(String);