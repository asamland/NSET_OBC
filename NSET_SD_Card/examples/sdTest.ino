#include <NSET.h>

nsetSD card(1);
String str = "hello";
const char *file = "datalog.txt";

void setup() {

}

void loop() {
  if(!card.SDWrite(str,file)){
    card.SDinit();
  }
  delay(1000);
 }
