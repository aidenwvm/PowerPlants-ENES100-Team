#include <BasicLinearAlgebra.h>

void motorSetup(int en, int in1, int in2)
{
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void drive(float vx, float vy, float wz) // vx and vy in mm/s, wz in rad/s
{
  float r = 25; //wheel radius (mm)
  float lx = 81; //distance from the center to the wheels in the x direction (mm)
  float ly = 91; //distance from the center to the wheels in the y direction (mm)

  BLA::Matrix<3> speedVector = {vx,vy,wz};
  BLA::Matrix<4,3> conversionMatrix = 
    {
      1,1,-(lx+ly),
      -1,1,(lx+ly),
      -1,1,-(lx+ly),
      1,1,(lx+ly)
    };
  conversionMatrix *= (1/r);
  
  BLA::Matrix<4> wheelVector;
  wheelVector = conversionMatrix*speedVector; //linear algebra!!! this part does all the reverse kinematics to find the wheel angular velocities in terms of the desired output velocities

  float wfl;
  float wfr;
  float wrl;
  float wrr;
  wfl = wheelVector(0);
  wfr = wheelVector(1);
  wrl = wheelVector(2);
  wrr = wheelVector(3); //gives the desired angular velocities of the wheels

  float sfl;
  float sfr;
  float srl;
  float srr;
  float wConversion = 255/(85*(2*M_PI/60)); //conversion multiplier between angular velocity and 0-255 range for analogWrite -- 85 is the max rpm of the motors
  sfl = wConversion*wfl;
  sfr = wConversion*wfr;
  srl = wConversion*wrl;
  srr = wConversion*wrr; //gives the speeds to write with analogWrite

  analogWrite(enLF, abs(sfl));
  analogWrite(enLR, abs(sfr));
  analogWrite(enRF, abs(srl));
  analogWrite(enRR, abs(srr)); //controls motor speeds

  if(sfl>=0){
    digitalWrite(inLF1, HIGH);
    digitalWrite(inLF2, LOW);
  } else {
    digitalWrite(inLF1, LOW);
    digitalWrite(inLF2, HIGH);
  }

  if(sfr>=0){
    digitalWrite(inRF1, HIGH);
    digitalWrite(inRF2, LOW);
  } else {
    digitalWrite(inRF1, LOW);
    digitalWrite(inRF2, HIGH);
  }

  if(srl>=0){
    digitalWrite(inLR1, HIGH);
    digitalWrite(inLR2, LOW);
  } else {
    digitalWrite(inLR1, LOW);
    digitalWrite(inLR2, HIGH);
  }

  if(srr>=0){
    digitalWrite(inRR1, HIGH);
    digitalWrite(inRR2, LOW);
  } else {
    digitalWrite(inRR1, LOW);
    digitalWrite(inRR2, HIGH); //controls motor directions
  }
}

void stop()
{
  analogWrite(enLF, 0);
  analogWrite(enLR, 0);
  analogWrite(enRF, 0);
  analogWrite(enRR, 0);
  
  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, LOW);
}

//-----------------------------------------------------------------------------------------------------------------------


// old motor code VV

void setMotorSpeed(float speed)
{
  analogWrite(enLF, speed);
  analogWrite(enLR, speed);
  analogWrite(enRF, speed*1.05);
  analogWrite(enRR, speed*1.05);
}

void driveForward(float speed)
{
  setMotorSpeed(speed);

  digitalWrite(inLF1, HIGH);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, HIGH);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, HIGH);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, HIGH);
  digitalWrite(inRR2, LOW);
}

void turnLeft(float speed)
{
  setMotorSpeed(speed);
  
  digitalWrite(inLF1, HIGH);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, HIGH);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, HIGH);
  digitalWrite(inRR1, HIGH);
  digitalWrite(inRR2, LOW);
}

void turnRight(float speed)
{
  setMotorSpeed(speed);
  
  digitalWrite(inRF1, HIGH);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, HIGH);
  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, HIGH);
  digitalWrite(inLR1, HIGH);
  digitalWrite(inLR2, LOW);
}

void backup(float speed)
{
  setMotorSpeed(speed);

  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, HIGH);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, HIGH);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, HIGH);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, HIGH);
}

