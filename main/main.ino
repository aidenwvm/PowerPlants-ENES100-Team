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
float distanceFront;
const int trigPin1 = 28;
const int echoPin1 = 29;

float distanceRight;
const int trigPin2 = 51;
const int echoPin2 = 50;

float distanceLeft;
const int trigPin3 = 46;
const int echoPin3 = 47;

//Servos
Servo armServo;
float armAngle = 90; //stores last angle written to servo
float armHeight = 140;

Servo tweezerServo;
float tweezerAngle = 90;

//Force probe
int forceProbeSensor = A0;

enum BotState 
{
  ORIENT,
  GO_TO_MISSIONSITE,
  PERFORM_MISSION,
  SKIP_MISSION,
  SCOOT_LEFT,
  DRIVE_TO_BAR, 
  SCOOT_RIGHT, 
  DRIVE_UNDER,
  MISSION_COMPLETE
};

BotState currentState = SKIP_MISSION;

void setup() 
{
  Serial.begin(9600);

  //Enes100.begin("PowerPlants", SEED, 595, 1201, A8, A9);
  //Enes100.println("PowerPlants connected");

  ultrasonicSetup(trigPin1, echoPin1);
  ultrasonicSetup(trigPin2, echoPin2);
  ultrasonicSetup(trigPin3, echoPin3);

  tweezerServo.attach(43);
  tweezerServo.write(90);
  armServo.attach(37);
  
  armServo.write(90);

  motorSetup(enLF, inLF1, inLF2);
  motorSetup(enLR, inLR1, inLR2);
  motorSetup(enRF, inRF1, inRF2);
  motorSetup(enRR, inRR1, inRR2);
}

void loop() 
{
  //display data on vision system monitor
  //Enes100.print("X = "); Enes100.println(Enes100.getX());
  //Enes100.print("Y = "); Enes100.println(Enes100.getY());
  //Enes100.print("Theta = "); Enes100.println(Enes100.getTheta());

  //get ultrasonic data
  distanceFront = getDistance(trigPin1, echoPin1);
  if(distanceFront < 0)
  {
    distanceFront = 1000;
  }
  //distanceRight = getDistance(trigPin2, echoPin2);
  distanceLeft = getDistance(trigPin3, echoPin3);
  if(distanceLeft < 0)
  {
    distanceLeft = 1000;
  }
  delay(10); //delay to protect ultrasonics

  
  //run current navigation/mission step
  switch(currentState)
  {
    //orient towards mission box
    case ORIENT:
      orient(M_PI/2);
      currentState = GO_TO_MISSIONSITE;
      break;

    //go to mission box
    case GO_TO_MISSIONSITE:
      if(distanceFront > 15)
      {
        driveForward(100);
      }
      else
      {
        stop();
        currentState = PERFORM_MISSION;
      }
      break;

    //analyze box for plantable substrate, plant seed, recover rock sample
    case PERFORM_MISSION:
      break
      ;

    //NEED TO ADD REORIENTATION STEP

    case SKIP_MISSION:
      //orient(0);
      driveForward(100);
      delay(2000);
      currentState = SCOOT_LEFT;
      break;

    //scoot left towards the wall until we're 5cm away
    //500 ms of scooting travels about 25cm
    case SCOOT_LEFT:
      if(distanceLeft > 2 && distanceLeft != 0)
      {
        goLeft(100);
      }
      else
      {
        goLeft(100);
        delay(1000);
        stop();
        currentState = DRIVE_TO_BAR;
      }
      break;
  
    //drive forwards until 30cm away from bar
    case DRIVE_TO_BAR:
      if(distanceFront > 30)
      {
        driveForward(100);
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
      }
      else
      {
        stop();
        currentState = DRIVE_UNDER;
      }
      break;

    //drive under bar
    case DRIVE_UNDER: 
      armServo.write(45);
      delay(500);
      driveForward(100);
      delay(7000);
      stop();
      currentState = MISSION_COMPLETE;
      break;

    case MISSION_COMPLETE:
      stop();
      drive(0,0,1);
      armServo.write(90);
      break;
  }
}



void orient(float angle) //orients the OTV to face in the stated direction based on the vision system's grid
{
  float theta = Enes100.getTheta();

  //imma assume the vision system works in radians
  //assume xy plane
  while(theta > (angle + 0.1) || theta < (angle - 0.1))
  {
    turnLeft(50);
    theta = Enes100.getTheta();
    Enes100.println(theta);
  }
  stop();

  /*
  distanceFront = getDistance(trigPin1, echoPin1);

  if(distanceFront < 35)
  {
    while(theta < -M_PI/2 + 0.03 || theta > -M_PI/2 - 0.03)
    {
      turnLeft(100);
    }
  }

  stop();
  */
}

void ultrasonicSetup(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

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