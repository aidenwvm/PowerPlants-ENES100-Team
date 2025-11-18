void motorSetup(int en, int in1, int in2)
{
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void setMotorSpeed(int speed)
{
  analogWrite(enLF, speed);
  analogWrite(enLR, speed);
  analogWrite(enRF, speed);
  analogWrite(enRR, speed);
}

void driveForward(int speed)
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

void turnLeft(int speed)
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

void turnRight(int speed)
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

void stop()
{
  setMotorSpeed(0);
  
  digitalWrite(inLF1, LOW);
  digitalWrite(inLF2, LOW);
  digitalWrite(inLR1, LOW);
  digitalWrite(inLR2, LOW);
  digitalWrite(inRF1, LOW);
  digitalWrite(inRF2, LOW);
  digitalWrite(inRR1, LOW);
  digitalWrite(inRR2, LOW);
}

void backup(int speed)
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
