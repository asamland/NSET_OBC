/*
nsetSD.h SD card written for teensy 3.5 for Northwestern NSET
written by Alex Samland | January 2019
MIT License
*/


#ifndef __NSET_H__
#define __NSET_H__

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

class NSET
{
  public:
    NSET(int debug=0);
    void SDinit(void);
    int SDWrite(String dataString, const char *filename="DATALOG.TXT");
  private:
    const int _chipSelect = BUILTIN_SDCARD;
    int _debug;
};

#endif
