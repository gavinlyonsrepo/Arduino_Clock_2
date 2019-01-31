
Overview
--------------------
* Name : clock_number_2
* Title : Arduino Real Time Alarm Clock and Lamp.
* Description : Arduino Clock with Battery backup (real time clock), Time, Date, Alarm, Temperature, LCD output, remote control input, Sleep mode, LED lighting (10X) with 10 light modes
* Author: Gavin Lyons

Libraries
------------------------
In src folder you will find the ino file with source code
it includes a number of libraries.

* <Wire.h>  //I2C communications
* <LiquidCrystal_I2C.h>// LCD
* <DS1302.h> //Real time clock
* <IRremote.h> //IR remote control
* <Sleep_n0m1.h> //For sleep mode https://github.com/n0m1/Sleep_n0m1

All are standard libraries which can be found on Arduino website, 
site except "sleep_n0m1", see link.


Parts List
------------------------------
See eagle diagram in "doc" schematic. 


>LCD module 16X2 I2C module
>
>Arduino UNO rev 3 or NANO.
>
>Remote control, 38kHz carrier frequency NEC.
>
>DS 1302 Real Time Clock module (with CR2032 battery)
>
>LM35 temperature sensor
>
>one active piezo buzzer (alarm)
>
>One VS1838 NEC Infrared IR Wireless Remote Control Sensor Module
>
>10 Leds( 5 red 5 bright blue)  10 current limiting  resistors (5 220 ohms 5 150 ohms) values depend on on how current user needs and specs of LEDS. 
>

Led calculations in this design:

Red Vd of 2V, Vcc-Vd/Rs = 13mA. Bright Blue Vd 3, Vcc-Vd/Rs = 13mA.
Total current consumption of LED circuit = 130mA.

Schematic
---------------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_2/blob/master/doc/eagle/clock2.png)


Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
