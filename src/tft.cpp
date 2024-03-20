#include <tft.h>
#include "bitmap.h"
#include <SPI.h>
#include <stdint.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void t_print_img(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);

void init_tft(){
  tft.init(240, 240, SPI_MODE3);  
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);

  t_print_img(0,0,T_BGC,240,240);

  // t_print("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
}

static uint16_t pgm_read_word2(const void* addr) {
  uint32_t res;
  __asm__ ( \
    "ssa8l %2 \n"  /* SAR = (AR[`addr`] & 3) * 8; */ \
    "srl %0, %1"    /* AR[`res`] = AR[`word`] >> SAR; */ \
    : "=r"(res) : "r"(*__pgm_cast_u32ptr(addr)), "r"(addr));
    res = ((uint16_t) res >> 8) | ((uint16_t) res << 8);
  return res;  
}

void t_print(String text){
  int16_t cursor_x = tft.getCursorX();
  int16_t cursor_y = tft.getCursorY();

  int16_t range_x = 100;
  int16_t range_y = 100;

  int16_t w= 240;
  int16_t h= 240;


  tft.setAddrWindow(0, 0, w, h);
  tft.startWrite(); 

  for (int16_t j = 0; j < range_y; j++) {
    for (int16_t i = 0; i < range_x; i++) {  
      int16_t ii = i ; 
      SPI1U1 = (SPI1U1 & ~(SPIMMOSI << SPILMOSI)) | ((15) << SPILMOSI);
      SPI1W0 = pgm_read_word2(T_BGC + j*w + ii);
      SPI1CMD |= SPIBUSY;
    }
  }
  
  tft.endWrite();

  tft.print(text);
}

void t_print_img(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h) {
  tft.setAddrWindow(x, y, w, h);
  tft.startWrite(); 

  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++) {  
      int16_t ii = i+x+y*w; 
      const void* addr = bitmap + j*w + ii;
      SPI1U1 = (SPI1U1 & ~(SPIMMOSI << SPILMOSI)) | ((15) << SPILMOSI);
      SPI1W0 = pgm_read_word2(addr);
      SPI1CMD |= SPIBUSY;
    }
  }
  
  tft.endWrite();
}
