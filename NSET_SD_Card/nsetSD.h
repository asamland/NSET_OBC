/*
nsetSD.h SD card written for teensy 3.5 for Northwestern NSET
written by Alex Samland | January 2019
MIT License
*/


#ifndef nsetSD_h
#define nsetSD_h

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

class nsetSD
{
  public:
    nsetSD( int debug);
    int SDWrite( char dataString);
  private:
    int _debug;
};

#endif
