
Overview
--------------------
* Name : clock_number_2
* Title : Arduino Real Time Alarm Clock with Temperature and LED lights. Remote controlled
* Description : Arduino Clock with Battery backup (real time clock), Time, Date, Alarm, Temperature, LCD output, remote control input, Sleep mode, LED lighting (10X) with 10 light modes
* Author: Gavin Lyons

Libraries
------------------------
* <Wire.h>  //I2C comms
* <LiquidCrystal_I2C.h>// LCD
* <DS1302.h> //Ral time clock
* <IRremote.h> //IR remote control
* <Sleep_n0m1.h> //https://github.com/n0m1/Sleep_n0m1

All can be found on Arduino website site except "sleep_n0m1"

Parts List
------------------------------
See fritzing diagram in "doc" for assembly instruction.

>LCD module 16X2 I2C module
>
>Arduino UNO rev 3
>
>Remote control 38kHz carrier frequency NEC.
>
>DS 1302 Real Time Clock module (with CR2032 battery)
>
>9 Volt power supply unit or battery
>
>LM35 temperature sensor
>
>10 Leds  10 current limiting  resistors 5 220ohms 5 68 ohms
>
>one active piezo buzzer (alarm)
>
>One VS1838 NEC Infrared IR Wireless Remote Control Sensor Module
>
>one enclosure

Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
