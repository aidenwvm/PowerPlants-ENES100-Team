int getForce()
{
  return analogRead(forceProbeSensor);
}

//this is based off of code for the old arm servo
/*
float testProbe() 
{
  float final_height = 80.0; //change according to actual final height(mm)
  float start_height = 140.0; //change according to actual start height(mm)
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
*/

float testProbe()
{
  float maxForce = 0;
  float currentForce = 0;
  armAngle = 90;

  while(armAngle > 20)
  {
    if(armAngle < 60)
    {
      backup(40); //helps probe go down straighter
    }

    armServo.write(armAngle);
    currentForce = getForce();
    Serial.println(currentForce);
    if(currentForce > maxForce)
    {
      maxForce = currentForce;
    }
    armAngle--;
    delay(50);
  }
  stop();

  for(int i=0;i<100;i++)
  {
    currentForce = getForce();
    Serial.println(currentForce);
    if(currentForce > maxForce)
    {
      maxForce = currentForce;
    }
    delay(10);
  }

  return maxForce;
}

enum PlanterBox 
{
  BACK_LEFT,
  BACK_RIGHT,
  FRONT_LEFT,
  FRONT_RIGHT
};

void analyzeMissionBox() //returns which box to plant in [MUST BE RUN AFTER ALIGNING TO THE MISSION BOX]
{
  PlanterBox plantableBox = BACK_LEFT; //by default we plant in the back left box

  float frontRight = 0;
  frontRight = testProbe();

  while(distanceFront > 5){
    driveForward(100);
    distanceFront = getDistance(trigPin1,echoPin1);
  }
  stop();

  float backRight = 0;
  backRight = testProbe();

  //need to move to back to test left side
  //need to move back to the front to prepare for planting
}