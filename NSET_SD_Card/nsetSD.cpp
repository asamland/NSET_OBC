#include "Arduino.h"
#include "nsetSD.h"
#include "SPI.h"
#include "SD.h"

nsetSD::nsetSD(int debug)
{
  _debug = debug;
  SPI.setMOSI(11);  // Audio shield has MOSI on pin 7
  SPI.setSCK(13);  // Audio shield has SCK on pin 14

  // Open serial communications and wait for port to open:
  if (_debug) {
   Serial.begin(9600);
   Serial.print("Initializing SD card...");
   Serial.print(_chipSelect);
  if (!SD.begin(_chipSelect&&_debug)) {
    Serial.println("Card failed, or not present");
  }else if (_debug){
    Serial.println("card initialized.");
  }

}

int nsetSD::SDWrite(const char* dataString)
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  char filename[] = "DataFile.txt";
  File dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    return 1;
  }
  // if the file isn't open, pop up an error:
  else {
    if (_debug){
      //Serial.println("error opening datalog.txt");
    }
    return 0;
  }
}
