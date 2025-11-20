#include <math.h>

//1325ms = 90 degrees
//1750ms = 45 degrees
void liftArmAngle(float angle) //angle in degrees
{
  float us = ((1325-1750)/(90-45))*(angle-90)+1325;
  armServo.writeMicroseconds(us);
}

void liftArmHeight(float height) //height in mm 
{
  float angle = (180/M_PI)*asin(height / 140);
  liftArmAngle(angle);
  armHeight = height;
}



