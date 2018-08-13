#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <fauxmoESP.h>

#define WIFI_SSID "D-Link_DIR-600M"
#define WIFI_PASS "Venu4lak"
#define SERIAL_BAUDRATE 115200

fauxmoESP fauxmo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUDRATE);

  setupWiFi();

  fauxmo.addDevice("Plant Watering");
  fauxmo.addDevice("Water Filter");

  fauxmo.onMessage(callback);
}

void setupWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("Successfully Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  fauxmo.handle();
}

void callback(uint8_t device_id, const char * device_name, bool state) 
{
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) 
  {
    Serial.println("ON");
  } 
  else 
  {
    Serial.println("OFF");
  }
}
