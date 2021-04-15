# Ambient Light Sensor

Cheap ambient light sensor to set monitor brightness.

## Hardware

- STM32F4-based board (e.g. BlackPill from Aliexpress)
- TSL2561 Luminosity sensor breakout board

It can work with more STM32 models with minor modifications.

## Wiring

Sensor works with 3.3v
Firmware uses interface I2C1 to communicate with the sensor (`B6 -> SCL`, `B7 -> SDA` on STM32F401)

## Build

The makefile uses `arm-none-eabi-gcc` as a compiler.

Build with `make -f STM32Make.make`

Flash with `make -f STM32Make.make flash` or manually flash `build/light_sensor.bin` with [st-flash](https://github.com/stlink-org/stlink)
