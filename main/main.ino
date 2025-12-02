#include "Enes100.h"
#include <Servo.h>

//Motors
//left front motor
int enLF = 7;
int inLF1 = 6;
int inLF2 = 5;

//left rear motor
int enLR = 13;
int inLR1 = 11;
int inLR2 = 12;

//right front motor
int enRF = 2;
int inRF1 = 4;
int inRF2 = 3;

//right rear motor
int enRR = 8;
int inRR1 = 9;
int inRR2 = 10;

int currentSpeed;


//Ultrasonics
int distanceFront;
const int trigPin1 = 53;
const int echoPin1 = 52;

int distanceRight;
const int trigPin2 = 20;
const int echoPin2 = 21;

int distanceLeft;
const int trigPin3 = 53;
const int echoPin3 = 52;

//Servos
Servo armServo;
int posArmServo = 2100;
float armAngle = 90; //stores last angle written to servo
float armHeight = 140; //stores last height written to servo

Servo tweezerServo;
int posTweezerServo = 0;

//Force probe
int forceProbeSensor = A0;

enum BotState 
{
  ORIENT,
  GO_TO_MISSIONSITE,
  PERFORM_MISSION,
  SCOOT_LEFT,
  DRIVE_TO_BAR, 
  SCOOT_RIGHT, 
  DRIVE_UNDER,
  MISSION_COMPLETE
};

BotState currentState = SCOOT_LEFT;

void setup() 
{
  Serial.begin(9600);

  //Enes100.begin("Simulator", SEEDPLANTING, 065, 1116, 8, 9);
  //Enes100.println("Connected...");

  //ultrasonicSetup(trigPin1, echoPin2);
  //ultrasonicSetup(trigPin2, echoPin2);
  //ultrasonicSetup(trigPin3, echoPin3);
  //Serial.begin(9600);

  tweezerServo.attach(43);
  tweezerServo.write(90);
  armServo.attach(37);

  //motorSetup(enLF, inLF1, inLF2);
  //motorSetup(enLR, inLR1, inLR2);
  //motorSetup(enRF, inRF1, inRF2);
  //motorSetup(enRR, inRR1, inRR2);
}

void loop() 
{
  //Enes100.print("X = "); Enes100.println(Enes100.getX());
  //Enes100.print("Y = "); Enes100.println(Enes100.getY());
  //Enes100.print("Theta = "); Enes100.println(Enes100.getTheta());

  //distanceFront = getDistance(trigPin1, echoPin1);
  //distanceRight = getDistance(trigPin2, echoPin2);
  //distanceLeft = getDistance(trigPin3, echoPin3);


  switch(currentState)
  {
    case ORIENT:

    break;

    //go to mission box
    case GO_TO_MISSIONSITE:

      if(distanceFront > 15)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      else
      {
        stop();
        currentState = PERFORM_MISSION;
      }

      break;

    case PERFORM_MISSION:

      // liftArmAngle(90);
      // delay(1000);
      // liftArmAngle(30);
      // delay(500);
      // tweezerServo.write(80);
      // delay(500);
      // liftArmHeight(90,30);

      break;

    //scoot left towards the wall until we're 5cm away
    //500 ms of scooting travels about 25cm
    case SCOOT_LEFT:

      if(distanceLeft > 5 && distanceLeft != 0)
      {
        goLeft(100);
        distanceLeft = getDistance(trigPin3, echoPin3);
      }

      else
      {
        stop();
        currentState = DRIVE_TO_BAR;
      }
    
      break;
  
    //drive forwards until 30cm away from bar
    case DRIVE_TO_BAR:

      if(distanceFront > 30)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      else
      {
        stop();
        currentState = SCOOT_RIGHT;
      }

      break;

    //scoot right 50cm
    case SCOOT_RIGHT:

      if(distanceLeft < 50)
      {
        goRight(100);
        distanceLeft = getDistance(trigPin3, echoPin3);
      }

      else
      {
        stop();
        currentState = DRIVE_UNDER;
      }

      break;

    //drive under bar
    case DRIVE_UNDER: 

      if(distanceFront > 15)
      {
        driveForward(100);
        distanceFront = getDistance(trigPin1, echoPin1);
      }

      else
      {
        stop();
        currentState = MISSION_COMPLETE;
      }

      break;

    case MISSION_COMPLETE:

      stop();
  }
}

/*
void ultrasonicSetup(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
*/


/*
void orient()
{
  //should probably add a check to see if would be quicker to orient right or left
  while(Enes100.getTheta() > 0.05 || Enes100.getTheta() < -0.05)
  {
    if(Enes100.getTheta() > 0.2 || Enes100.getTheta() < -0.2)
    {
      stop();
    }

    else
    {
      turnLeft()
      delay(1);
      stop();
    }
  }
}
*/

float getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);

  return duration * 0.034 / 2;
}


// BAD VV DOES NOT WORK DO NOT USE RAHHHHH
/*
void movePlatformHeight(float height) //note: this moves the OTV base at a constant speed, while the speed of the platform should vary; this means that for small heights, it could go very fast
{
 if(height > armHeight){
    for(int i = armHeight; i < height; i++)
    {
      liftArmHeight(armHeight+1);
      float dDrive = sqrt(sq(140)-sq(armHeight-1))-sqrt(sq(140)-sq(armHeight)); //small distance to drive the OTV
      driveDistance(0,dDrive,150,false); //setting this to not stop should make it move smoother
    }
  } else if(height < armHeight)
  {
    for(int i = armHeight; i > height; i--)
    {
      liftArmHeight(armHeight-1);
      float dDrive = -sqrt(sq(140)-sq(armHeight-1))-sqrt(sq(140)-sq(armHeight)); //small distance to drive the OTV
      driveDistance(0,dDrive,150,false); //setting this to not stop should make it move smoother
    }
  }
  stop();
  armHeight = height;
}
*/
