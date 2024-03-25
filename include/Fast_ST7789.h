#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 

#ifndef _FAST_ST7789H_
#define _FAST_ST7789H_

class Fast_ST7789 : public Adafruit_ST7789 {
  public:
    Fast_ST7789(int8_t cs, int8_t dc, int8_t rst);
    void test(uint16_t x, uint16_t y, const uint16_t bitmap[], uint16_t w, uint16_t h);
    uint32_t pgm_read_word2(const uint16_t* addr);
};

#endif // _FAST_ST7789H_