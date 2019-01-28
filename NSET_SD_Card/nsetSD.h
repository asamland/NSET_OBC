/*
nsetSD.h SD card written for teensy 3.5 for Northwestern NSET
written by Alex Samland | January 2019
MIT License
*/


#ifndef __NSETSD_H__
#define __NSETSD_H__

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

class nsetSD
{
  public:
    nsetSD(int debug=0);
    int SDWrite(String dataString, String filename="DATALOG.TXT")
  private:
    const int _chipSelect = BUILTIN_SDCARD;
};

#endif
