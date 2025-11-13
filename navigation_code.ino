#include "Enes100.h"
#include <Servo.h>

int distanceFront;
const int trigPin1 = 11;
const int echoPin1 = 12;

int distanceRight;
const int trigPin2 = 20;
const int echoPin2 = 21;

int distanceLeft;
const int trigPin3 = 25;
const int echoPin3 = 26;

Servo armServo;
int posArmServo = 2100;

Servo tweezerServo;
int posTweezerServo = 0;

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

void setup() 
{
  //Enes100.begin("Simulator", SEEDPLANTING, 065, 1116, 8, 9);
  //Enes100.println("Connected...");

  //ultrasonicSetup(trigPin1, echoPin2);
  //ultrasonicSetup(trigPin2, echoPin2);
  //ultrasonicSetup(trigPin3, echoPin3);
  //Serial.begin(9600);

  armServo.attach(37);
  //tweezerServo.attach(9);

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


/*  //test to find actual threshold
  if(distanceRight > 1 && distanceLeft > 1 && distanceFront > 10)
  {
    driveForward();
  } 

  else if(distanceFront < 10 && distanceRight < distanceLeft)
  {
    while(Enes100.getTheta() > -pi/2)
    {
      turnLeft();
      delay(1);
    }
  } 

  else if (distanceFront < 10 && distanceLeft < distanceRight)
  {
    while(Enes100.getTheta() < pi/2)
    {
      turnRight();
      delay(1)
    }
  }
  */

  liftArm();
}

/*
void ultrasonicSetup(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
*/

void motorSetup(int en, int in1, int in2)
{
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

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
void driveForward()
{
  digitalWrite(enLF, HIGH);
  digitalWrite(enLR, HIGH);
  digitalWrite(enRF, HIGH);
  digitalWrite(enRR, HIGH);

  digitalWrite(inLF1, HIGH);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, HIGH);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, HIGH);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, HIGH);
  digitalWrite(inRR2, LOW);

  delay(1000);

  //test to find a better acceleration threshold
  for(int i = 0; i < 90; i += 10)
  {
    analogWrite(enLF, i);
    analogWrite(enLR, i);
    analogWrite(enRF, i);
    analogWrite(enRR, i);

    delay(10);
    currentSpeed = i;
  }
}

void turnLeft()
{
  digitalWrite(enLF, HIGH);
  digitalWrite(enLR, HIGH);
  digitalWrite(enRF, HIGH);
  digitalWrite(enRR, HIGH);
  
  digitalWrite(inLF1, HIGH);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, HIGH);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, HIGH);
  digitalWrite(inRR1, HIGH);
  digitalWrite(inRR2, LOW);

  delay(975);

  /*//test to find better speed threshold for turning so shit doesn't go flying
  for(int i = 0; i < 45; i += 5)
  {
    analogWrite(enLF, i);
    analogWrite(enLR, i);
    analogWrite(enRF, i);
    analogWrite(enRR, i);

    delay(10);
    currentSpeed = i;
  }*/

  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, LOW);
}

void turnRight()
{
  digitalWrite(enLF, HIGH);
  digitalWrite(enLR, HIGH);
  digitalWrite(enRF, HIGH);
  digitalWrite(enRR, HIGH);
  
  digitalWrite(inRF1, HIGH);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, HIGH);
  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, HIGH);
  digitalWrite(inLR1, HIGH);
  digitalWrite(inLR2, LOW);

  delay(975);
  /*
  for(int i = 0; i < 45; i += 5)
  {
    analogWrite(enLF, i);
    analogWrite(enLR, i);
    analogWrite(enRF, i);
    analogWrite(enRR, i);

    delay(10);
    currentSpeed = i;
  }*/
}

void stop()
{
  /*for(int i = currentSpeed; i > 0; i -= 10)
  {
    analogWrite(enLF, i);
    analogWrite(enLR, i);
    analogWrite(enRF, i);
    analogWrite(enRR, i);

    delay(10);
  }

  currentSpeed = 0;*/
  
  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, LOW);
 
  digitalWrite(enLF, 0);
  digitalWrite(enLR, 0);
  digitalWrite(enRF, 0);
  digitalWrite(enRR, 0);
}

void backup()
{
  digitalWrite(enLF, HIGH);
  digitalWrite(enLR, HIGH);
  digitalWrite(enRF, HIGH);
  digitalWrite(enLR, HIGH);

  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, HIGH);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, HIGH);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, HIGH);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, HIGH);

  delay(1000);

  for(int i = 0; i < 90; i += 10)
  {
    analogWrite(enLF, i);
    analogWrite(enLR, i);
    analogWrite(enRF, i);
    analogWrite(enRR, i);

    delay(10);
    currentSpeed = i;
  }
}

//1325 = 90 degrees
//1750 = 45 degrees
void liftArm()
{
  armServo.writeMicroseconds(1750);

  // for(posArmServo = 2100; posArmServo > 1000; posArmServo--)
  // {
  //     armServo.writeMicroseconds(posArmServo);
  //     delay(50);
  // }
}
  
