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

float testprobe() 
{
  float final_height = 80.0; //change according to actual final height(mm)
  float start_height = 100.0; //change according to actual start height(mm)
  float speed = 30.0; //change based on actual starting speed(deg/s)

  liftArmHeight(start_height, speed);
  speed = 10.0; //slow speed for descent of arm - can also change based on actual speed wanted

  String data = "";

  float height = start_height;
  float maxForce = 0; //keeps track of highest force

  //going down
  while(height > final_height)
  {
    height--;
    liftArmHeight(height, speed);
    float force = getForce();
    data = data + String(force) + " "; 

    if(force > maxForce)
    {
      maxForce = force;
    }
  }

  //going back up
  while(height < start_height)
  {
    height++;
    liftArmHeight(height, speed);
    float force = getForce();
    data = data + String(force) + " ";

    if(force > maxForce)
    {
      maxForce = force;
    }
  }

  return maxForce;
}

int runFPtest()
{
  float force1 = 0;
  float force2 = 0;
  float force3 = 0;
  float force4 = 0;

  bool isOrzo1 = false;
  bool isOrzo2 = false;
  bool isOrzo3 = false;
  bool isOrzo4 = false;

  distanceFront = getDistance(trigPin1, echoPin1);

  while(distanceFront > 10 && distanceFront != 0)
  {
    driveForward(100);
    distanceFront = getDistance(trigPin1, echoPin1);
  }

  force1 = testprobe();  
  
  //find benchmark to distinguish between orzo and rocks
  if(force1 > 800)
  {
    isOrzo1 = true;
    orzoBin = 1;

    return orzoBin;
  }

  else
  {
    distanceFront = getDistance(trigPin1, echoPin1);

    while(distanceFront > 2 && distanceFront != 0)
    {
      driveForward(100);
      distanceFront = getDistance(trigPin1, echoPin1);
    }

    force2 = testprobe();  

    if(force2 > 800)
    {
      isOrzo2 = true;
      orzoBin = 2;

      return orzoBin;
    }

    else
    {
      distanceFront = getDistance(trigPin1, echoPin1);

      while(distanceFront < 10 && distanceFront != 0)
      {
        backup(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      distanceLeft = getDistance(trigPin3, echoPin3);

      while(distanceLeft < 60)
      {
        goRight(100);
        distanceLeft = getDistance(trigPin3, echoPin3);
      }

      distanceFront = getDistance(trigPin1, echoPin1);

      while(distanceFront < 10 && distanceFront != 0)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      drive(0, 0, 0.2);
      delay(975);
      stop();

      distanceFront = getDistance(trigPin1, echoPin1);

      while(distanceFront < 10 && distanceFront != 0)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      drive(0, 0, -0.2);
      delay(975);
      stop();

      distanceFront = getDistance(trigPin1, echoPin1);

      while(distanceFront > 10 && distanceFront != 0)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      force3 = testprobe();  

      if(force3 > 800)
      {
        isOrzo3 = true;
        orzoBin = 3;

        return orzoBin;
      }

      else
      {
        distanceFront = getDistance(trigPin1, echoPin1);

        while(distanceFront > 2 && distanceFront != 0)
        {
          driveForward(100);
          distanceFront = getDistance(trigPin1, echoPin1);
        }

        force4 = testprobe();  

        if(force4 > 800)
        {
          isOrzo4 = true;
          orzoBin = 4;

          return orzoBin;
        }
      }
    }
  }
}
