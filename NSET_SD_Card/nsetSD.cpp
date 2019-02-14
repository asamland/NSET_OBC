#include <NSET.h>

nsetSD::nsetSD(int debug)
{

  // Open serial communications and wait for port to open:
  _debug = debug;
  SDinit();
}

void nsetSD:: SDinit(void)
{
  // Open serial communications and wait for port to open:
  if (_debug){
    Serial.begin(9600);
    while (!Serial);
    Serial.print("Initializing SD card...");
  }

  // see if the card is present and can be initialized:
  if (!SD.begin(_chipSelect)) {
    if (_debug)
    {
      Serial.println("Card failed, or not present");
    }
    // don't do anything more:
    return;
  }
  if (_debug)
  {
    Serial.println("card initialized.");
  }
}

int nsetSD:: SDWrite(String dataString, const char *filename)
{
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    if (_debug)
    {
      Serial.println(dataString);
    }
    return 1;
  }
  // if the file isn't open, pop up an error:
  else {
    if (_debug){
      Serial.println("error opening datalog.txt");
    }
    return 0;
  }
}
