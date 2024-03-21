#include <tft.h>
#include "bitmap.h"
#include <SPI.h>
#include <stdint.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void t_print_img(uint16_t x, uint16_t y, const uint16_t bitmap[], uint16_t w, uint16_t h);

void init_tft(){
  unsigned long time;

  tft.init(240, 240, SPI_MODE3);  
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);

  time = micros();
  t_print_img(0,0,T_BGC,240,240);
  unsigned long dt = micros()-time;
  Serial.println(dt);
  // t_print("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
}

static uint16_t pgm_read_word2(const uint16_t* addr) {
  uint16_t res, res1;
//   __asm__ (
//     "ssa8l %3"  /* SAR = (AR[`addr`] & 3) * 8; */\
//     "srl %0, %1" /* AR[`res`] = AR[`word`] >> SAR; */\
//     "ssa8l %4"  /* SAR = (AR[`addr`] & 3) * 8; */\
//     "srl %2, %5"   /* AR[`res`] = AR[`word`] >> SAR; */\
//     : "=r"(res), "=r"(res1)\
//     : "r"(*__pgm_cast_u32ptr(addr)), "r"(addr), "r"(*__pgm_cast_u32ptr(addr+1)), "r"(addr+1)
// );

  __asm__ ( \
    "ssa8l %2 \n"  /* SAR = (AR[`addr`] & 3) * 8; */ \
    "srl %0, %1"    /* AR[`res`] = AR[`word`] >> SAR; */ \
    : "=r"(res) : "r"(*__pgm_cast_u32ptr(addr)), "r"(addr));
  __asm__ ( \
    "ssa8l %2 \n"  /* SAR = (AR[`addr`] & 3) * 8; */ \
    "srl %0, %1"    /* AR[`res`] = AR[`word`] >> SAR; */ \
    : "=r"(res1) : "r"(*__pgm_cast_u32ptr(addr+1)), "r"(addr+1));

  return (res >> 8) | (res << 8) | (((res >> 8) | (res << 8))<<16);  
}

// void t_print(String text){
//   int16_t cursor_x = tft.getCursorX();
//   int16_t cursor_y = tft.getCursorY();

//   int16_t range_x = 100;
//   int16_t range_y = 100;

//   int16_t w= 240;
//   int16_t h= 240;


//   tft.setAddrWindow(0, 0, w, h);
//   tft.startWrite(); 

//   for (int16_t j = 0; j < range_y; j++) {
//     for (int16_t i = 0; i < range_x; i++) {  
//       int16_t ii = i ; 
//       SPI1U1 = (SPI1U1 & ~(SPIMMOSI << SPILMOSI)) | ((15) << SPILMOSI);
//       SPI1W0 = pgm_read_word2(T_BGC + j*w + ii);
//       SPI1CMD |= SPIBUSY;
//     }
//   }
  
//   tft.endWrite();

//   tft.print(text);
// }

void t_print_img(uint16_t x, uint16_t y, const uint16_t bitmap[], uint16_t w, uint16_t h) {
  volatile uint32_t * fifoPtr;;
  uint32_t dataSize;

  tft.setAddrWindow(x, y, w, h);
  tft.startWrite(); 

  for (uint32_t i = 0; i < w*h/32; i++) {  
    fifoPtr = &SPI1W0;
    dataSize = 16;

    SPI1U1 = (SPI1U1 & ~(SPIMMOSI << SPILMOSI)) | ((511) << SPILMOSI);
    while(SPI1CMD & SPIBUSY) {}

    while(dataSize--) {
      *(fifoPtr++) = pgm_read_word2(bitmap++);
      bitmap++;
    }
    
    // __sync_synchronize();
    SPI1CMD |= SPIBUSY;
    // while(SPI1CMD & SPIBUSY) {}
    
  }
  
  tft.endWrite();
}
