#include <math.h>

//1325ms = 90 degrees
//1750ms = 45 degrees
void liftArmAngle(float angle) //angle in degrees
{
  float us = ((1325-1750)/(90-45))*(angle-90)+1325;
  armServo.writeMicroseconds(us);

  armAngle = angle;
}

void liftArmHeight(float height, float speed) //height in mm, speed in deg/s 
{
  float angle = (180/M_PI)*asin(height / 140);

  if(angle > armAngle)
  {
    for(float i=armAngle;i<angle;i++)
    {
      liftArmAngle(armAngle+1);
      delay(1000*1/speed);
    }
  } else if(angle < armAngle)
  {
    for(float i=armAngle;i>angle;i--)
    {
      liftArmAngle(armAngle-1);
      delay(1000*1/speed);
    }
  }

  armHeight = height;
}



