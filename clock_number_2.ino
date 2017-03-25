 
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
#include <IRremote.h>
#include <Sleep_n0m1.h> //https://github.com/n0m1/Sleep_n0m1

//LEDS
// BlueLed1 = 2;
// BlueLed2 = ~9;
// BlueLed3 = 4;
// BlueLed4 = !~3;
// BlueLed5 = 13;
// RedLed1 = 17;
// RedLed2 = 12;
// RedLed3  =16;
// RedLed4 =~10;
// RedLed5  =!~11;
int ledPins[] = { 
  2, 9, 4, 3, 13, 17, 12, 16, 10, 11};       // an array of pin numbers to which LEDs are attached
int pinCount = 10; 
int Ledmodecount = 10;

//remote
const int irReceiverPin = 8;  
IRrecv irrecv(irReceiverPin); 
decode_results results; 


//Alarm
#define Buzzer 15
char alarm[4] = {'X','X','X','X'};  

//lm35
#define tempPin A0
float temp;
  

/* DS1302  */
uint8_t CE_PIN   = 5;  //RST pin attach to
uint8_t IO_PIN   = 6;  //
uint8_t SCLK_PIN = 7;
char buf[4];
char day[10];
char Timedate[15];
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

//sleepmode 
Sleep sleep;


//LCD
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int tim = 1000;  //the value of delay time
boolean LCDbacklightOn = false;
boolean LCDDisplayOn = false;

void setup() 
{
  Serial.begin(9600); //baud  
  // put your setup code here, to run once:
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  LCDbacklightOn == true;
  LCDDisplayOn == true;

  //clock
  rtc.write_protect(false);
  rtc.halt(false);
  
  //buzzer
  pinMode(Buzzer,OUTPUT);
  
  //IR remote
  irrecv.enableIRIn();  

  //LED Outputs
    for (int thisPin = 0; thisPin < pinCount; thisPin++)  
    {
       //  Serial.println(thisPin);
        pinMode(ledPins[thisPin], OUTPUT);      
    }

   //init lcd info
   lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Real Time Clock");
               lcd.setCursor(0,1);
               lcd.print("Alarm Lamp");
               delay(1500);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("By Gavin Lyons");
               delay(1000);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("Press INFO/MENU");
               lcd.setCursor(0,1);
               lcd.print("for Remote Help");
               delay(2000);
               lcd.clear();
}

void loop() 
{
  
  // put your main code here, to run repeatedly: 
   if (irrecv.decode(&results)) 
   {   
        DecodeIR();
        irrecv.resume();
        delay(500);    
   }  
  //print date and time
  print_time();
  //print temp
  LM35Display();
  //set LEDs
  LEDMode();
}

void LM35Display()

{
  
  temp = analogRead(tempPin);
  //Serial.println(temp);
  temp = temp * .48828125;
 // Serial.println(temp);
  temp = temp - 1;
 //Serial.println(temp);
  lcd.setCursor(10,1);
  lcd.print("T");
  lcd.print(temp);
  delay(200);
}

void print_time()
{
    /* DS1302  */
    Time t = rtc.time();
    /**/
    memset(day, 0, sizeof(day));

    /* buf */
        sprintf(buf, "%02d%02d%02d%02d%02d", t.hr, t.min ); // format time date day in string
     
      //Serial.println(buf);
    switch (t.day)
    {
    case 1: strcpy(day, "Sun"); break;
    case 2: strcpy(day, "Mon"); break;
    case 3: strcpy(day, "Tue"); break;
    case 4: strcpy(day, "Wed"); break;
    case 5: strcpy(day, "Thu"); break;
    case 6: strcpy(day, "Fri"); break;
    case 7: strcpy(day, "Sat"); break;
    }
     
    
       
    //check alarm time
    if ((buf[0] == alarm[0]) && (buf[1] == alarm[1]) && (buf[2] == alarm[2]) &&  (buf[3] == alarm[3]))
        {
          //turn on  alarm
          digitalWrite(Buzzer,HIGH);    
          lcd.backlight();  //open the backlight 
          lcd.display();
          LCDbacklightOn == true;
          LCDDisplayOn == true;
          Ledmodecount = 8;
               
        }   
        
    /* LCD */    
    lcd.setCursor(0,0);
    lcd.print(t.date/10);
    lcd.print(t.date%10);
    lcd.print("-");
    lcd.print(t.mon/10);
    lcd.print(t.mon%10);
    lcd.print("-");
    lcd.print(t.yr);
    lcd.print(" ");
    lcd.print(day);   
    lcd.setCursor(0,1);
    lcd.print(t.hr);
    lcd.print(":");
    lcd.print(t.min/10);
    lcd.print(t.min%10);
    lcd.print(":");
    lcd.print(t.sec/10);
    lcd.print(t.sec%10);
    //print alarm symbol A
   if ( 'X' != alarm[0])
    {
      lcd.setCursor(15,0);
      lcd.print("A");
    }
     delay(200);
}




void LEDMode()
{
  // Serial.println(Ledmodecount);
  int x=0;
  switch(Ledmodecount)
  {
  case 0: //all off
    for (int thisPin = 0; thisPin < pinCount; thisPin++) 
    {       
    // turn the pin off:
   
    digitalWrite(ledPins[thisPin], LOW);
     }
  break;
  
  case 1: //all on
    for (int thisPin = 0; thisPin < pinCount; thisPin++) 
    {       
    // turn the pin on:
  // Serial.println(Ledmodecount);
    digitalWrite(ledPins[thisPin], HIGH);
     }
  break;
  
  case 2: //red on blue off
     for (int thisPin = 5; thisPin < pinCount; thisPin++) 
    {       
    // turn the pin on:
      digitalWrite(ledPins[thisPin], HIGH);
     }
     
    for (int thisPin = 0; thisPin < 5; thisPin++) 
    {       
    // turn the pin off:
       digitalWrite(ledPins[thisPin],LOW);
     }
  break;
  
  case 3: //blue on red off
    for (int thisPin = 5; thisPin < pinCount; thisPin++) 
      {       
        digitalWrite(ledPins[thisPin], LOW);
     }
     for (int thisPin = 0; thisPin < 5; thisPin++) 
      {       
        digitalWrite(ledPins[thisPin],HIGH);
     }
  break;
  
  case 4: //Temp led bar  graph         
          for (int thisPin = 0; thisPin < pinCount; thisPin++) 
            {       
            // turn the pins:
           
            digitalWrite(ledPins[thisPin], LOW);
             }
          x = int(temp);         
          x = (x/3);
          if (x < 1)
            {
              x =1;
            }
          if (x > 10)
             {
              x = 10;
             }
            // Serial.println(x);
           for (int thisPin = 0; thisPin < x; thisPin++) 
            {       
                digitalWrite(ledPins[thisPin], HIGH);
            }
    break;
  
  
  case 5://delay blink
     for (int thisPin = 0; thisPin < pinCount; thisPin++) 
     {      
        //on
        digitalWrite(ledPins[thisPin], HIGH);
     }
     delay(800);
     for (int thisPin = 0; thisPin < pinCount; thisPin++) 
     {     
    // turn  off:
        digitalWrite(ledPins[thisPin], LOW);
     }
  break;
  
   case 6: //pwm on 5 and 6 leds array two reds 
           for (int thisPin = 0; thisPin < pinCount; thisPin++) 
            {       
            // turn the pins:
           
            digitalWrite(ledPins[thisPin], LOW);
             }
   // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
  
    analogWrite(ledPins[1], fadeValue);
    analogWrite(ledPins[8], fadeValue);
   
    // wait for 30 milliseconds to see the dimming effect
    delay(25);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
   
    analogWrite(ledPins[1], fadeValue);
    analogWrite(ledPins[8], fadeValue);
    
    // wait for 30 milliseconds to see the dimming effect
    delay(25);
  }
   break;
  
  case 7: //Cylon
    for (int thisPin = 0; thisPin < pinCount; thisPin++) 
      {      
        digitalWrite(ledPins[thisPin], HIGH);
        delay(250);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
      }
     for (int thisPin = 10; thisPin >= 0; thisPin--) 
      {      
        digitalWrite(ledPins[thisPin], HIGH);
        delay(250);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
      }
       
   break;
    
  case 8: //blink red delay blink blue 
        //red on 
         for (int thisPin = 5; thisPin < pinCount; thisPin++) 
    {       
    // turn the pin on:
      digitalWrite(ledPins[thisPin], HIGH);
     }
     
    for (int thisPin = 0; thisPin < 5; thisPin++) 
    {       
    // turn the pin off:
       digitalWrite(ledPins[thisPin],LOW);
     }
     delay(800);
     for (int thisPin = 5; thisPin < pinCount; thisPin++) 
      {       
        digitalWrite(ledPins[thisPin], LOW);
     }
     for (int thisPin = 0; thisPin < 5; thisPin++) 
      {       
        digitalWrite(ledPins[thisPin],HIGH);
     }
     
     break;
    case 9: // Random
         int ranNumpins;
         int ranPinstart;
         ranNumpins=random(0,11);
        
         for (int thisPin = 0; thisPin < pinCount; thisPin++) 
          {       
          // turn the pin off:
         digitalWrite(ledPins[thisPin], LOW);
           }
           
           for (ranNumpins ; ranNumpins < pinCount; ranNumpins++) 
            {       
            // turn the pin on:
           
            digitalWrite(ledPins[ranNumpins], HIGH);
             }
             delay(500);
         break;
  }
}


void DecodeIR()
{
    //decode remote first Beko remote second Chorus remote
    Serial.println("irCode: ");            
    Serial.println(results.value, HEX); 
    
    switch (results.value)
    {
      case (0x820): //backlight power button mode LCD display
      case (0xE17A48B7): //Backlight power button
        if (LCDbacklightOn == false)
        {
          lcd.backlight();
        }
        else 
        {
          lcd.noBacklight();
        }
        LCDbacklightOn = !LCDbacklightOn;
        delay(500);
        if (LCDDisplayOn == false)
        {
          lcd.display();
        }
        else 
        {
          lcd.noDisplay();
        }
        LCDDisplayOn = !LCDDisplayOn;
        
        break;

         case (0x82A): //avtv
         case (0xE17AA45B)://guide
               //sleep mode toogle                            
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Enter Sleep Mode");
              lcd.setCursor(0,1);
              lcd.print("Wake on Alarm");
              delay(1000);
              lcd.clear();
             SleepMode()     ;               
        break;
        
        case (0x80A)://Buzzer Test play SUB button
        case (0xE17A24DB)://Buzzer Test TV/VCR
           digitalWrite(Buzzer,HIGH);
          delay(1000);
          digitalWrite(Buzzer,LOW);
             
        break;
        
        case (0x80E)://Display alarm Test REVEAL
        case (0xE17AB847)://Text
               DisplayAlarm();
        break;

        case (0x80F): //set alarm UPDATE
        case (0xE17AF807)://subtiltes
              SetAlarm();
         break;

         case (0x80C): //Stop Alarm STOP
         case (0xE17AF00F)://mute
              Ledmodecount = 0 ;
              digitalWrite(Buzzer,LOW);
              for (int x = 0; x <= 3; x++)
              {     
                  alarm[x] = 'X';
              }
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Alarm Stop Reset");
              delay(1000);
              lcd.clear();
         break;
         
         case (0x829): //menu help
              HelpBeko();
          break;
         case (0xE17A7887)://info 
               HelpChorus();
          break;
               
            case (0x824): //plus Led mode VOL+
            case (0xE17A847B)://radio  
            //  Serial.println(Ledmodecount);
              if (Ledmodecount <10) {
                Ledmodecount ++;
              }
                
         break;
         case (0x825): //minus Led mode VOL-
            case (0xE17A04FB)://Audio 
              if (Ledmodecount >0) {
                Ledmodecount --;
              }
              
         break;
          case (0x828): //set time date OK
          case (0xE17AA857): //OK  
              SetTime();
             
         break;
         
         case (0x804): //ir debug MIX
         case (0xE17A8877)://menu     
              IRdebug();
             
         break;
        case (0x810):case (0xE17A00FF): Ledmodecount = 0;break;
        case (0x811):case (0xE17A807F): Ledmodecount = 1;break;
        case (0x812):case (0xE17A40BF): Ledmodecount = 2;break;
        case (0x813):case (0xE17AC03F): Ledmodecount = 3;break;
        case (0x814):case (0xE17A20Df): Ledmodecount = 4;break;
        case (0x815):case (0xE17AA05F): Ledmodecount = 5;break;
        case (0x816):case (0xE17A609F): Ledmodecount = 6;break;
        case (0x817):case (0xE17AE01F): Ledmodecount = 7;break;
        case (0x818):case (0xE17A10EF): Ledmodecount = 8;break; 
        case (0x819):case (0xE17A906F): Ledmodecount = 9;break;   
     
    }   
    
    
}


void SetTime()
{
  //clear variables
  int z = 0;
  int i = 1;
  char key= 'a';
  irrecv.resume();
  delay(500); 
  
  
  //init lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Date time");
  lcd.setCursor(0,1);
  lcd.print("W=Day,Sun=1");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HHMMDDMMYYYYW");
  lcd.setCursor(0,1);
  
  //loop to get time date
  while (i < 14)
  {  
    if (irrecv.decode(&results))
    {
    Serial.println("irCode: ");            
    Serial.println(results.value, HEX);
    switch (results.value)
    {
      case (0x810):case (0xE17A00FF):key = '0';break;
      case (0x811):case (0xE17A807F):key = '1';break;
      case (0x812):case (0xE17A40BF):key = '2';break;
      case (0x813):case (0xE17AC03F):key = '3';break;
      case (0x814):case (0xE17A20Df):key = '4';break;
      case (0x815):case (0xE17AA05F):key = '5';break;
      case (0x816):case (0xE17A609F):key = '6';break;
      case (0x817):case (0xE17AE01F):key = '7';break;
      case (0x818):case (0xE17A10EF):key = '8';break; 
      case (0x819):case (0xE17A906F):key = '9';break;   
     
    }     
        
        if (key >= '0' && key <='9') 
        {
          Timedate[z] = key;
          z++;
          i++;
          lcd.print(key);  
          key = 'a'; 
        }
        irrecv.resume();
        delay(500);        
    }  
  }
  //Serial.println(Timedate);
  lcd.clear();
  int Hour =0;
  int Min =0;
  int Date =0;
  int Month =0;
  int Year = 0;
  int Day =  0;
  
   (sscanf(Timedate, "%02d%02d%02d%02d%04d%01d", &Hour, &Min, &Date, &Month, &Year,&Day));

 
  Time t(Year, Month , Date,Hour, Min, 30, Day);
  // Set the time and date on the chip */
  rtc.time(t);
}

void IRdebug()

{
    lcd.clear();
    irrecv.resume();
    delay(500);  
    lcd.setCursor(0,0);
    lcd.print("IR debug code");
    
    while (results.value != (0x820) && results.value != (0xE17A48B7) ) //or results.value != (0xE17A48B7))
    {
      if (irrecv.decode(&results))
      {
        lcd.setCursor(0,1);
        lcd.print(results.value,HEX);
        delay(3000);
        irrecv.resume();
        delay(500); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("IR debug code");
      }
    }
    lcd.clear();
}

void SetAlarm()
{
  //clear variables
  int z = 0;
  int i = 1;
  char key= 'a';
  irrecv.resume();
  delay(500);  
  
  //LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HHMM : SET Alarm");
  lcd.setCursor(0,1);

  //loop to get alarm
  while (i < 5)
  {  
    if (irrecv.decode(&results))
    {
    Serial.println("irCode: ");            
    Serial.println(results.value, HEX);
    switch (results.value)
    {
      case (0x810):case (0xE17A00FF):key = '0';break;
      case (0x811):case (0xE17A807F):key = '1';break;
      case (0x812):case (0xE17A40BF):key = '2';break;
      case (0x813):case (0xE17AC03F):key = '3';break;
      case (0x814):case (0xE17A20Df):key = '4';break;
      case (0x815):case (0xE17AA05F):key = '5';break;
      case (0x816):case (0xE17A609F):key = '6';break;
      case (0x817):case (0xE17AE01F):key = '7';break;
      case (0x818):case (0xE17A10EF):key = '8';break; 
      case (0x819):case (0xE17A906F):key = '9';break;   
    
    }     
        
        if (key >= '0' && key <='9') 
        {
          
          alarm[z] = key;
          z++;
          i++;
          lcd.print(key);  
          key = 'a'; 
        }
        irrecv.resume();
        delay(500); 
    }
    
   
  }
  
  DisplayAlarm();
 
  
}

void DisplayAlarm()
{
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Alarm HHMM");
               lcd.setCursor(0,1);
               lcd.print("      ");
               for (int x = 0; x <= 3; x++)
              {     
                  lcd.print(alarm[x]);
              }
               
               delay(2000);
               lcd.clear();
}

void HelpBeko()
{
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Help for ");
               lcd.setCursor(0,1);
               lcd.print("Remote Beko");
               delay(2000);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("ON=LCD sleep");
               lcd.setCursor(0,1);
               lcd.print("AvTv=Sleepmode");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("Stop=Alarm off");
               lcd.setCursor(0,1);
               lcd.print("SUB=Alarm test");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("Revel=Alarm Show");
               lcd.setCursor(0,1);
               lcd.print("Update=Alarm Set");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("Menu=Help");
               lcd.setCursor(0,1);
               lcd.print("OK=Set Date Time");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("VOL+ = LED MODE +1");
               lcd.setCursor(0,1);
               lcd.print("VOL- = LED MODE -1");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("1-9=LED MODEs");
               lcd.setCursor(0,1);
               lcd.print("0=LEDs off");
               delay(2000);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("Mix= IR debug");
               delay(1000);
               lcd.clear();
}

void HelpChorus ()
{
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Help for ");
               lcd.setCursor(0,1);
               lcd.print("Chorus remote");
               delay(2500);
               lcd.clear();

               
              lcd.setCursor(0,0);
               lcd.print("ON=LCD off");
               lcd.setCursor(0,1);
               lcd.print("guide=Sleepmode");
               delay(2000);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("Mute=Alarm off");
               lcd.setCursor(0,1);
               lcd.print("TV/VCR=Buzz");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("Text=Alarm show");
               lcd.setCursor(0,1);
               lcd.print("Sub/t=Alarm Set");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("INFO=Help");
               lcd.setCursor(0,1);
               lcd.print("OK=Date Time");
               delay(2000);
               lcd.clear();

               lcd.setCursor(0,0);
               lcd.print("Radio=LED MODE+1");
               lcd.setCursor(0,1);
               lcd.print("Audio=LED MODE-1");
               delay(2000);
               lcd.clear();
                  
               lcd.setCursor(0,0);
               lcd.print("1-9=LED MODEs");
               lcd.setCursor(0,1);
               lcd.print("0=LEDs off");
               delay(2000);
               lcd.clear();
               
               lcd.setCursor(0,0);
               lcd.print("MENU= IR debug");
               delay(1000);
               lcd.clear();
}         

void SleepMode() 
{
   
    //set LEDs
    Ledmodecount = 0 ;
    LEDMode();
    lcd.noBacklight();  //turn off
    lcd.noDisplay();
    int loopforever =1;
    do 
    {    
    Serial.println("sleep");
     delay(100); //delay to allow work before sleep      
      sleep.pwrDownMode(); //set sleep mode
      sleep.sleepDelay(50000); //sleep 
      delay(100);
       Serial.println(buf);
        Serial.println(alarm);
      //check alarm time
      /* DS1302  */
      Time t = rtc.time();
         /* buf */
        sprintf(buf, "%02d%02d%02d%02d%02d", t.hr, t.min ); // format time date day in string
      if ((buf[0] == alarm[0]) && (buf[1] == alarm[1]) && (buf[2] == alarm[2]) &&  (buf[3] == alarm[3]))
          {       
          Serial.println("alarm");
          return;
          } 
//           
//       if (irrecv.decode(&results)) 
//       {   
//          Serial.println("remote");
//          lcd.backlight();
//          lcd.display();
//          return;   
////       }  
    } while (loopforever < 50);
  //   Serial.println("wake");
}


