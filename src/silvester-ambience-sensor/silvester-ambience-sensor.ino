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
int lora_complete = 0;
void onEvent(ev_t event) {
  switch(event) {
    case EV_SCAN_TIMEOUT:
      Serial.println("EV_SCAN_TIMEOUT");
      lora_complete = -1;
      break;
    case EV_BEACON_FOUND:
      Serial.println("EV_BEACON_FOUND");
      break;
    case EV_BEACON_MISSED:
      Serial.println("EV_BEACON_MISSED");
      break;
    case EV_BEACON_TRACKED:
      Serial.println("EV_BEACON_TRACKED");
      break;
    case EV_JOINING:
      Serial.println("EV_JOINING");
      break;
    case EV_JOINED:
      Serial.println("EV_JOINED");
      LMIC_setLinkCheckMode(0);
      break;
    case EV_RFU1:
      Serial.println("EV_RFU1");
      break;
    case EV_JOIN_FAILED:
      Serial.println("EV_JOIN_FAILED");
      lora_complete = -1;
      break;
    case EV_REJOIN_FAILED:
      Serial.println("EV_REJOIN_FAILED");
      lora_complete = -1;
      break;
    case EV_TXCOMPLETE:
      Serial.println("EV_TXCOMPLETE (Includes waiting for RX windows)");

      if(LMIC.txrxFlags & TXRX_ACK) {
        Serial.println("Received ACK");
      }

      if(LMIC.dataLen) {
        Serial.print("Received ");
        Serial.print(LMIC.dataLen);
        Serial.println(" bytes of payload");
      }

      lora_complete = 1;
      break;
    case EV_LOST_TSYNC:
      Serial.println("EV_LOST_TSYNC");
      break;
    case EV_RESET:
      Serial.println("EV_RESET");
      break;
    case EV_RXCOMPLETE:
      Serial.println("EV_RXCOMPLETE");
      lora_complete = 1;
      break;
    case EV_LINK_DEAD:
      Serial.println("EV_LINK_DEAD");
      lora_complete = -1;
      break;
    case EV_LINK_ALIVE:
      Serial.println("EV_LINK_ALIVE");
      break;
    case EV_SCAN_FOUND:
      Serial.println("EV_SCAN_FOUND");
      break;
    case EV_TXSTART:
      Serial.println("EV_TXSTART");
      break;
    case EV_TXCANCELED:
      Serial.println("EV_TXCANCELED");
      lora_complete = -1;
      break;
    case EV_RXSTART:
      break;
    case EV_JOIN_TXCOMPLETE:
      Serial.println("EV_JOIN_TXCOMPLETE: No JoinAccept");
      lora_complete = -1;
      break;

    default:
      Serial.print("Unknown event: ");
      Serial.println((unsigned) event);
      break;
  }
}
bool sendLoraPayload(byte* payload, size_t size) {
  if(LMIC.opmode & OP_TXRXPEND) {
    Serial.println("OP_TXRXPEND, not sending");
    return false;
  }

  lora_complete = 0;
  LMIC_setTxData2(1, payload, size, 0);
  while(lora_complete == 0) {
    Serial.print(" ");
    os_runloop_once();
  }

  Serial.println();

  return lora_complete == 1;
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
