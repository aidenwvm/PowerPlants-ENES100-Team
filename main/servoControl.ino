#include <cmath>

//1325 = 90 degrees
//1750 = 45 degrees
void liftArmAngle(float angle) //angle in degrees
{
  float us = ((1325-1750)/(90-45))*(angle-90)+1325;
  servoArm.writeMicroseconds(us);
}

void liftArmHeight(float height) //height in mm 
{
  float angle = asin(height / 140);
  liftArmAngle(angle);
}



