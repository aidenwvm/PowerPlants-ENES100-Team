float final_height = 80.0; //change according to actual final height(mm)
float start_height = 100.0; //change according to actual start height(mm)
float speed = 30.0; //change based on actual starting speed(deg/s)

liftArmHeight(start_height, speed);
speed = 10.0; //slow speed for descent of arm - can also change based on actual speed wanted

String data = "";

float height = start_height;

//going down
while(height > final_height){
  height--;
  liftArmHeight(height, speed);
  Serial.println(getForce()); 
}

//going back up
while(height < start_height){
  height++;
  liftArmHeight(height, speed);
  Serial.println(getForce()); 
}
