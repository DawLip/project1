#include "Fast_ST7789.h"

Fast_ST7789::Fast_ST7789(int8_t cs, int8_t dc, int8_t rst)
    : Adafruit_ST7789(cs, dc, rst) {}

// uint32_t Fast_ST7789::pgm_read_word2(const uint16_t* addr) {
//   uint32_t res, res1;  
//     // __asm__ volatile( 
//     // "ssa8l %[ad] \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
//     // "srl %[r1], %[pad]\n"    /* AR[`res`] = AR[`word`] >> SAR; */ 
//     // "ssa8l %[ad1] \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
//     // "srl %[r2], %[pad1]"    /* AR[`res`] = AR[`word`] >> SAR; */ 
//     // : 
//     // [r1]"=r"(res),
//     // [r2]"=r"(res1)
//     // : 
//     // [pad]"r"(*__pgm_cast_u32ptr(addr)), 
//     // [ad]"r"(addr), 
//     // [pad1]"r"(*__pgm_cast_u32ptr(addr+1)), 
//     // [ad1]"r"(addr+1));
// __asm__ ( 
//     "ssa8l %2 \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
//     "srl %0, %1"    /* AR[`res`] = AR[`word`] >> SAR; */ 
//     : "=r"(res) : "r"(*__pgm_cast_u32ptr(addr)), "r"(addr));
// __asm__ ( 
//   "ssa8l %2 \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
//   "srl %0, %1"    /* AR[`res`] = AR[`word`] >> SAR; */ 
//   : "=r"(res1) : "r"(*__pgm_cast_u32ptr(addr+1)), "r"(addr+1));

// Serial.println(res, HEX);
// Serial.println(res1, HEX);

// res =(res >> 8) | (res<< 8);
// res1 =(res1 >> 8) | (res1<< 8);

//   return res | (uint32_t)(res1)<<16;  
// }

uint32_t Fast_ST7789::pgm_read_word2(const uint16_t* addr) {
  uint32_t r1,r2,r3,r4,r5,r6;  
    // __asm__ volatile( 
    // "ssa8l %[ad] \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
    // "srl %[r1], %[pad]\n"    /* AR[`res`] = AR[`word`] >> SAR; */ 
    // "ssa8l %[ad1] \n"  /* SAR = (AR[`addr`] & 3) * 8; */ 
    // "srl %[r2], %[pad1]"    /* AR[`res`] = AR[`word`] >> SAR; */ 
    // : 
    // [r1]"=r"(res),
    // [r2]"=r"(res1)
    // : 
    // [pad]"r"(*__pgm_cast_u32ptr(addr)), 
    // [ad]"r"(addr), 
    // [pad1]"r"(*__pgm_cast_u32ptr(addr+1)), 
    // [ad1]"r"(addr+1));
  // __asm__ ( 
  //     "mov %0, %1 \n"
  //     "ldi $r0, 0xff000000 \n"
  //     "and $r16, %0, $r0 \n"
  //     "ldi $r0, 0x0000ff00 \n"
  //     "and $r17, %0, $r0 \n"
  //     "slli %0, 8"
  //     : "=r"(r1)
  //     : 
  //     "r"(*__pgm_cast_u32ptr(addr))
  //     :
  //     "r16", "r17"
  //   );

  Serial.println(r1, HEX);


  // r1 =(res >> 8) | (res<< 8);
  // r2 =(res1 >> 8) | (res1<< 8);

  return r1;  
}

void Fast_ST7789::test(uint16_t x, uint16_t y, const uint16_t bitmap[], uint16_t w, uint16_t h){
volatile uint32_t * fifoPtr;;
  uint32_t dataSize;

  setAddrWindow(x, y, w, h);
  startWrite(); 

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
  
  endWrite();
}