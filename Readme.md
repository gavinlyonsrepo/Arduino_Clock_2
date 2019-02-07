
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

Led mode
--------------------------------
The modes are 

0. All Leds off
1. All Leds on
2. All red Leds on
3. All blues on
4. LEDs bargraph on based on temperature.(0-30C one LED = 3 degrees)
5. Blink all LEDS on and off 
6. Fade in and out with PWM all LEDs attached to PWM pins 
7. Cylon display  (led chaser)
8. Blink all red , blink all blue.
9. Random pattern


Parts List
------------------------------
See eagle diagram in "doc" schematic. 


>LCD module 16X2 with I2C module
>
>NANO Arduino module or UNO rev 3 
>
>DS 1302 Real Time Clock module (with CR2032 battery)
>
>LM35 temperature sensor
>
>one active buzzer 
>
>One VS1838 NEC Infrared IR Wireless Remote Control Sensor Module
>
>10 Leds( 5 red 5 bright blue)  10 current limiting resistors (5 220 ohms 5 150 ohms) 
>
>Remote control 38kHz carrier frequency NEC.(The Unit is designed for BEKO MODEL: B92187F or Chorus remote Model: Um4(AAA,r03) can easily be re-factored for others(which can communicate with Vs1838) by end user.  The unit includes an option to scan remotes and give the codes on LCD. 
[Remote control information](https://github.com/gavinlyonsrepo/Arduino_Clock_2/blob/master/doc) 
>

Some current calculations in this design:

Red Vd of 2V, Vcc-Vd/Rs = ~13mA. Bright Blue Vd 3, Vcc-Vd/Rs = ~13mA.
Total current consumption of LED circuit in theory = ~130mA.

Measured Current Consumption figures:

1. 55mA , normal mode
2. 31mA , Sleep mode
3. 38mA , normal mode + LCD off
4. 171mA , normal mode + All LEDS on

Schematic
---------------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_2/blob/master/doc/eagle/clock2.png)


Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
