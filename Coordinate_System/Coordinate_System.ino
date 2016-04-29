#include <Servo.h>
Servo servo[4];  // create servo object to control a servo

void setup()
{
  servo[0].attach(3);
  servo[1].attach(5);
  servo[2].attach(6);
  servo[3].attach(9);
  
  servo[0].write(50);
  servo[1].write(0);
  servo[2].write(142);
  servo[3].write(80);
  delay(1000);
  
  Serial.begin(9600);
}

void loop()
{
  int value[4];
  
  if (Serial.find("x")) {
    for(int i = 0; i < 4; i++){
      value[i] = Serial.parseInt();
      servo[i].write(value[i]);
    }
  }
}



