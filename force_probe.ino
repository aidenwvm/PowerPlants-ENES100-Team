#define pin A0

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int forceReading = analogRead(pin);
  Serial.println("Orzo: " + forceReading);
  delay(100); 
}
