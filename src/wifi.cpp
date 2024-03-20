#include <wifi.h>

void program_via_wifi();

void init_wifi(){
  Serial.println("Connecting to wifi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {delay(10);}

  Serial.println("Wifi connected");
  Serial.print("IPv4: ");
  Serial.println(WiFi.localIP());

  program_via_wifi();
}

void program_via_wifi(){
  ArduinoOTA.begin();
  ArduinoOTA.setHostname("esp8266");
}