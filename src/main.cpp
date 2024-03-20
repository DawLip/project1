#include <Arduino.h>

#include <wifi.h>
#include <tft.h>

unsigned long cur_time;

void setup(void) {
  ESP.wdtDisable();
  wdt_disable();
  Serial.begin(9600);
  Serial.println("\n\nINIT BEGIN\n"); 
 
  init_tft();
  // init_wifi();

  Serial.println("\nINIT SUCCESS");
}

void loop() {
  // ArduinoOTA.handle();
  ESP.wdtFeed();
}