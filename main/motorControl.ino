void motorSetup(int en, int in1, int in2)
{
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

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