int getForce()
{
  return analogRead(pin);
}

void forceProbeTest()
{
  int force = getForce();

  while(force < 800)
  {
    force = getForce();
    delay(10);
  }
}
