// #include "ESP8266WiFi.h"
// #include <MFRC522.h>
// #include <rfid.h>

// unsigned int getCardID(MFRC522);

// void mfrc522Handler(){
//   if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
//   if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  
//   Serial.println(getCardID(mfrc522));

//   mfrc522.PICC_HaltA();
// }

// unsigned int getCardID(MFRC522 mfrc522) {
//   unsigned int id;
  
//   id =  mfrc522.uid.uidByte[0] << 24;
//   id += mfrc522.uid.uidByte[1] << 16;
//   id += mfrc522.uid.uidByte[2] <<  8;
//   id += mfrc522.uid.uidByte[3];

//   return id;
// }