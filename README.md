# Ambient Light Sensor

A cheap ambient light sensor control monitor brightness automatically.  
This repo contains the firmware and a 3D-printable enclosure for a BlackPill board along with a simple holder for the luminosity sensor.

## Hardware

- STM32F4-based board (e.g. BlackPill)
- TSL2561 Luminosity sensor

It can work on various STM32 models with minor modifications.

## Wiring

Sensor works with 3.3v
Firmware uses interface I2C1 to communicate with the sensor (`B6 -> SCL`, `B7 -> SDA` on STM32F401)

## Build

The makefile uses `arm-none-eabi-gcc` as a compiler.

Build with `make -f STM32Make.make`

Flash with `make -f STM32Make.make flash` or manually flash `build/light_sensor.bin` with [st-flash](https://github.com/stlink-org/stlink)

## Software

I use [Clight](https://github.com/FedeDP/Clight) to control my monitor's brightness through [DDC](https://en.wikipedia.org/wiki/Display_Data_Channel).

### Clight config

Refer to [Clight's documentation]() for details

```
~/.config/clight.conf

...
sensor:
{
ac_regression_points = [ 0.02, 0.20, 0.30, 0.35, 0.40, 0.60, 0.74, 0.88, 0.93, 0.97, 1.0 ];
devname = "/dev/ttyALS";

# i: polling interval; m: min lux; M: max lux
settings = "i=400,m=0,M=4000";
# Number of sequential captures
captures = [ 5, 5 ];
}
...
```
