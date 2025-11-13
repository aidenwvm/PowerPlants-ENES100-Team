#include "Enes100.h"
//basic code for wifi communication, postion, and navigation

void setup() {
  Enes100.begin("POWERPLANTS", SEED, 205, 1116, 3, 2);
  Enes100.println("Connected...");
}

void loop() {
  float x, y, t; bool v;
  x = Enes100.getX();  
  y = Enes100.getY();  
  t = Enes100.getTheta();  
  v = Enes100.isVisible(); 

  if (v) {
    Enes100.print(x); 
    Enes100.print(",");
    Enes100.print(y);
    Enes100.print(",");
    Enes100.println(t);
  }
  else {
    Enes100.println("Not visible"); 
  }

  delay(1000);

}
