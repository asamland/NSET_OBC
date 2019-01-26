#include <nsetSD.h>

nsetSD SDcard();

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if(SDcard.SDWrite("hi")){
  Serial.write("hi");
  }

}
