#!/bin/python

import serial
import os
import subprocess

MAX_LUX = 300
MIN_BACKLIGHT = [8, 8]
MAX_BACKLIGHT = [65, 50]

ser = serial.Serial("/dev/ttyUSB0", 115200)
f = open("/home/bonnee/als", "w")

while ser:
    s = ser.readline()
    lux = int(bytes.decode(s).strip().strip("\x00"))
    print(f"got {lux} lux")
    f.seek(0)
    f.write(f"{lux}\n")
    f.truncate()

    # monitors = int(
    #    subprocess.check_output("ddcutil detect | grep Display | wc -l", shell=True)
    # )
    # for i in range(1, monitors + 1):
    #    lum = min(
    #        100,
    #        int(
    #            (lux - 1)
    #            * (MAX_BACKLIGHT[i - 1] - MIN_BACKLIGHT[i - 1])
    #            / (MAX_LUX - 1)
    #            + MIN_BACKLIGHT[i - 1]
    #        ),
    #    )
    #    print(f"monitor {i}: {lum}%")
    #    os.system(f"ddcutil setvcp 10 {lum} -d {i}")
