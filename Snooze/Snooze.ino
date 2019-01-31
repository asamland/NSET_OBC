

#include <SparkFun_I2C_GPS_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
I2CGPS myI2CGPS; //Hook object to the library

#include <TinyGPS++.h> //From: https://github.com/mikalhart/TinyGPSPlus
TinyGPSPlus gps; //Declare gps object
#include <Snooze.h>
#include <NSET.h>
// Load drivers
SnoozeDigital digital;
SnoozeCompare compare;
SnoozeTimer timer;
SnoozeAlarm  alarm;
NSET  SD1;

#define ALARM_S  20
SnoozeBlock config1(digital, timer);


void setup() {
    if (myI2CGPS.begin() == false)
    {
      //Serial.println("Module failed to respond. Please check wiring.");
      while (1); //Freeze!
    }
    pinMode(LED_BUILTIN,HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    
    /********************************************************
     Define digital pins for waking the teensy up. This
     combines pinMode and attachInterrupt in one function.
     
     Teensy 3.x
     Digtal pins: all pins
     ********************************************************/
    digital.pinMode(22, INPUT_PULLUP, FALLING);//pin, mode, type
    
    /********************************************************
     Teensy 3.x only currently.
     
     Set RTC alarm wake up in (hours, minutes, seconds).
     ********************************************************/
    //timer.setTimer(20000);// milliseconds
}

void loop() {
    int who;
    /********************************************************
     feed the sleep function its wakeup parameters. Then go
     to deepSleep.
     ********************************************************/
    who = Snooze.sleep( config1 );// return module that woke processor
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if(!SD1.SDWrite(String(who))){
    SD1.SDinit();
    SD1.SDWrite("failed");  
  }
  if (myI2CGPS.available()) //available() returns the number of new bytes available from the GPS module
  {
    gps.encode(myI2CGPS.read()); //Feed the GPS parser
  }

  if (gps.time.isUpdated()) //Check to see if new GPS info is available
  {
    displayInfo();
  }
}




String displayInfo()
{
  //We have new GPS data to deal with!
  String data;
  if (gps.time.isValid())
  {
    data = "Date: ";
    data+= String(gps.date.month());
    data+= "/";
    data+= String(gps.date.day());
    data+= "/";
    data+= String(gps.date.year());
    data+= " Time: ";
    if (gps.time.hour() < 10) data+="0";
    data += String(gps.time.hour());
    data += ":";
    if (gps.time.minute() < 10) data+="0";
    data+=String(gps.time.minute());
    data+=":";
    if (gps.time.second() < 10) data+="0";
    data+=String(gps.time.second());
    if(!SD1.SDWrite(data)){
      SD1.SDinit();
      SD1.SDWrite(data);
    }
  }

//    Serial.println(); //Done printing time
//  }
//  else
//  {
//    Serial.println(F("Time not yet valid"));
//  }
//
//  if (gps.location.isValid())
//  {
//    Serial.print("Location: ");
//    Serial.print(gps.location.lat(), 6);
//    Serial.print(F(", "));
//    Serial.print(gps.location.lng(), 6);
//    Serial.println();
//  }
//  else
//  {
//    Serial.println(F("Location not yet valid"));
//  }
}
