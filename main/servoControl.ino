#include <cmath>

//1325 = 90 degrees
//1750 = 45 degrees
void liftArm(float angle)
{
  float us = ((1325-1750)/(90-45))*(angle-90)+1325;
  servoArm.writeMicroseconds(us);
}

void liftArm(float height)
{
  float angle = asin(height / 140);
  liftArm(angle);
}
