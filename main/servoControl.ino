//1325 = 90 degrees
//1750 = 45 degrees
void liftArm(float angle)
{
  float us = ((1325-1750)/(90-45))*(angle-90)+1325;
  servoArm.writeMicroseconds(us);
}