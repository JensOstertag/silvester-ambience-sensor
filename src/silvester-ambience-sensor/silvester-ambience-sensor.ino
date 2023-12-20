// WeMos board: https://github.com/esp8266/Arduino

// Config
#include "config.h"

// LoRa (SX1276) - https://github.com/mcci-catena/arduino-lmic
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
const lmic_pinmap lmic_pins = {
  .nss = LORA_PIN_CS,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = LMIC_UNUSED_PIN,
  .dio = {LORA_PIN_DIO0, LORA_PIN_DIO1, LMIC_UNUSED_PIN}
};
void os_getArtEui(u1_t* buf) {
  u1_t appEui[8] = TTN_APP_EUI;
  memcpy_P(buf, appEui, 8);
}
void os_getDevEui(u1_t* buf) {
  u1_t devEui[8] = TTN_DEV_EUI;
  memcpy_P(buf, devEui, 8);
}
void os_getDevKey(u1_t* buf) {
  u1_t appKey[16] = TTN_APP_KEY;
  memcpy_P(buf, appKey, 16);
}

// Light sensor (BH1750) - https://github.com/claws/BH1750
#include <BH1750.h>
#include <Wire.h>
BH1750 lightSensor(LIGHTSENSOR_I2C_ADDR);

// Sound sensor (Generic microphone module)
// TODO

void setup() {
  Serial.begin(BAUD_RATE);

  // LoRa setup
  os_init();
  LMIC_reset();
  LMIC_setClockError(MAX_CLOCK_ERROR * LORA_CLOCK_ERROR);

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
