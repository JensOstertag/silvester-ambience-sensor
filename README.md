<div align="center">

![Header](img/header.jpg)

# Silvester ambience sensor

### LoRaWAN sensor measuring light and sound levels

Attempt to measure impact of pyrotechnics on light and sound levels during New Year's Eve

[Introduction](#introduction) • [Functionality](#functionality) • [Data](#data) • [Dependencies](#dependencies) • [License](#license)

<sub>Title image generated by [deepai.org](https://deepai.org/machine-learning-model/text2img)</sub>

</div>

## Introduction
During New Year's Eve, the air is polluted by - undoubtedly beautiful - fireworks, and other forms of pyrotechnics, and measurements show that it takes several hours or even days until the air quality reaches the same level as before. 
Another problem is the light and sound pollution, which is stressful specially for animals, but also for elderly people, children, or other people with special needs.
This project is an attempt to measure the impact of pyrotechnics on light and sound levels during New Year's Eve, and to raise awareness about the problem.

## Functionality
The sensor measures light and sound levels periodically, with an interval of roughly 30 seconds. The data is then sent to TTN (The Things Network) via LoRa with the LoRaWAN protocol. From there, it is sent to ThingSpeak, where it is stored and visualized.

### Hardware
The sensors main component is an ESP8266 microcontroller, specifically a WeMos D1 mini. It is connected to a SX1276 LoRa module, which is used to send data to TTN.
For the sensors, a BH1750 light sensor, connected via I2C, and a KY-037 microphone module, connected to an analog input of the ESP8266, are used. A better alternative to the KY-037 would be a MAX4466 microphone module, as it comes with an adjustable gain.

### Power
The device is powered by the WeMos' Micro-USB port, which is connected to a 5V power supply. It was desired to power it from a battery, for which the ESP8266 has a quite efficient power saving mode. For that, the D0 pin has to be connected to the RST pin. However, D0 was already used to connect the LoRa module, thus the power saving mode could not be used.
Theoretically, the device uses low enough power that it can also be powered by a modern-sized powerbank for up to a few days without the powerbank needing to be recharged.

## Data
The data will be measured on New Year's Eve 2023/24.

## Dependencies
The following tools and libraries are used:
- **Arduino IDE** - Download: [arduino.cc/en/software](https://www.arduino.cc/en/software), GitHub: [arduino/arduino-ide](https://github.com/arduino/arduino-ide)
- **ESP8266** - GitHub: [esp8266/Arduino](https://github.com/esp8266/Arduino), licensed under [LGPL-2.1 license](https://github.com/esp8266/Arduino/blob/master/LICENSE)
- **arduino-lmic** v0.10.0 - GitHub: [mcci-catena/arduino-lmic](https://github.com/mcci-catena/arduino-lmic), licensed under [MIT license](https://github.com/mcci-catena/arduino-lmic/blob/master/LICENSE)
- **BH1750** v1.3.0 - GitHub: [claws/BH1750](https://github.com/claws/BH1750), licensed under [MIT license](https://github.com/claws/BH1750/blob/master/LICENSE)
- **The Things Network** - Website: [thethingsnetwork.org](https://www.thethingsnetwork.org/), GitHub: [TheThingsNetwork/lorawan-stack](https://github.com/TheThingsNetwork/lorawan-stack)
- **ThingSpeak** - Website: [thingspeak.com](https://thingspeak.com/), GitHub: [iobridge/thingspeak](https://github.com/iobridge/thingspeak)

## License
The software of this project (located within the [`/src` directory](./src)) is licensed under the [MIT license](./LICENSE-MIT).
