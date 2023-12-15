// WeMos board: https://github.com/esp8266/Arduino

// Config
#include "config.h"

// LoRa (SX1276) - https://github.com/mcci-catena/arduino-lmic
// TODO

// Light sensor (BH1750) - https://github.com/claws/BH1750
#include <BH1750.h>
#include <Wire.h>
BH1750 lightSensor(LIGHTSENSOR_I2C_ADDR);

// Sound sensor (Generic microphone module)
// TODO

void setup() {
  Serial.begin(BAUD_RATE);

  // LoRa setup
  // TODO

  // Light sensor setup
  Wire.begin();
  if(!lightSensor.begin(LIGHTSENSOR_MODE)) {
    Serial.println("(Setup) Failed to setup light sensor");
  }

  // Sound sensor setup
  // TODO
}

void loop() {
  // Light sensor measurement
  float light = lightSensor.readLightLevel();
  Serial.print("light:");
  Serial.print(light);

  // Sound sensor measurement
  // TODO

  Serial.println();

  if(DEEP_SLEEP) {
    ESP.deepSleep(INTERVAL_SECONDS * 1000000);
  } else {
    delay(INTERVAL_SECONDS * 1000);
  }
}
