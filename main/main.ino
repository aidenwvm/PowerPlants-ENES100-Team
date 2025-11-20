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
const int trigPin1 = 11;
const int echoPin1 = 12;

int distanceRight;
const int trigPin2 = 20;
const int echoPin2 = 21;

int distanceLeft;
const int trigPin3 = 25;
const int echoPin3 = 26;

//Servos
Servo armServo;
int posArmServo = 2100;

Servo tweezerServo;
int posTweezerServo = 0;


void setup() 
{
  //Enes100.begin("Simulator", SEEDPLANTING, 065, 1116, 8, 9);
  //Enes100.println("Connected...");

  //ultrasonicSetup(trigPin1, echoPin2);
  //ultrasonicSetup(trigPin2, echoPin2);
  //ultrasonicSetup(trigPin3, echoPin3);
  //Serial.begin(9600);

  armServo.attach(37);
  liftArmHeight(140);  //running a lil testy
  
  /*
  tweezerServo.attach(31);
  tweezerServo.write(0);
  */

  //motorSetup(enLF, inLF1, inLF2);
  //motorSetup(enLR, inLR1, inLR2);
  //motorSetup(enRF, inRF1, inRF2);
  //motorSetup(enRR, inRR1, inRR2);

  //orient();
}

void loop() 
{
  //Enes100.print("X = "); Enes100.println(Enes100.getX());
  //Enes100.print("Y = "); Enes100.println(Enes100.getY());
  //Enes100.print("Theta = "); Enes100.println(Enes100.getTheta());

  //driveForward();
  //turnLeft();
  //delay(1000);
  //stop();

  //distanceFront = getDistance(trigPin1, echoPin1);
  //distanceRight = getDistance(trigPin2, echoPin2);
  //distanceLeft = getDistance(trigPin3, echoPin3);

  //go to mission box
  // while(distanceFront > 15)
  // {
  //    driveForward(100);
  //    distanceFront = getDistance(trigPin1, echoPin1);
  // }

  //stop();

  //scoot left towards the wall until we're 5cm away
  //500 ms of scooting travels about 25cm
  while(distanceLeft > 5)
  {
    goLeft(100);
    distanceLeft = getDistance(trigPin3, echoPin3);
    
    if(distanceLeft < 5)
    {
      break;
    }
  }

  //drive forwards until 30cm away from bar
  while(distanceFront > 30)
  {
    driveForward(100);
    distanceFront = getDistance(trigPin1, echoPin1);

    if(distanceFront < 30)
    {
      break;
    }
  }   

  stop();

  /*
  //scoot right 50cm
  while(distanceLeft < 50)
  {
     goRight(100);
     distanceLeft = getDistance(trigPin3, echoPin3);
  }

  stop();

  //drive under bar
  while(distanceFront > 15)
  {
   driveForward(100);
   distanceFront = getDistance(trigPin1, echoPin1);
  }
  */
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

int getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);

  return duration * 0.034 / 2;
}
*/

void movePlatformHeight(float height){ //note: this moves the OTV base at a constant speed, while the speed of the platform should vary; this means that for small heights, it could go very fast
 if(height > armHeight){
    direction = 1;
    for(int i = armHeight, i++, i >= height)
    {
      liftArmHeight(armHeight+1);
      float dDrive = sqrt(sq(140)-sq(armHeight-1))-sqrt(sq(140)-sq(armHeight)); //small distance to drive the OTV
      driveDistance(0,dDrive,100,FALSE); //setting this to not stop should make it move smoother
    }
  } else if(height < armHeight)
  {
    for(int i = armHeight, i--, i <= height)
    {
      liftArmHeight(armHeight-1);
      float dDrive = -sqrt(sq(140)-sq(armHeight-1))-sqrt(sq(140)-sq(armHeight)); //small distance to drive the OTV
      driveDistance(0,dDrive,100,FALSE); //setting this to not stop should make it move smoother
    }
  } else {
    break;
  }
  stop();
  armHeight = height;
}
