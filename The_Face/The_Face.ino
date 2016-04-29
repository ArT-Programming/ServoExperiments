#include <Servo.h>
#include <NAservo.h>

NAservo servo[4];

void setup()
{
  servo[0].Setup(9, 0, 180);
  servo[1].Setup(10, 0, 180);
  servo[2].Setup(3, 0, 180);
  servo[3].Setup(11, 0, 180);

  Serial.begin(9600);
  servo[0].MoveTo(50);
  servo[1].MoveTo(0);
  servo[2].MoveTo(142);
  servo[3].MoveTo(80);
  delay(1000);
}

void loop()
{
  /*for (int s = 0; s < 4; s++) {
    Serial.println(s);
    while (!servo[s].MoveTo(180, 50)) {}
    while (!servo[s].MoveTo(0, 50)) {}
  }
  Serial.println("Starting rest");
  while (!servo[0].MoveTo(50, 50)){}
  Serial.println("0 done");
  while (!servo[1].MoveTo(0, 50)){}
  Serial.println("1 done");
  while (!servo[2].MoveTo(142, 50)){}
  Serial.println("2 done");
  while (!servo[3].MoveTo(80, 50)){}
  Serial.println("3 done");

  Serial.println("Rest done");*/
  
  //delay(5000);
  //rise();
  //delay(1000);
  //lookOut();
  delay(500);
  lookOut();
  //delay(1000);
  //goDown();
}

void rest() {
  while (!servo[0].MoveTo(50, 150)){}
  while (!servo[1].MoveTo(0, 150)){}
  while (!servo[2].MoveTo(142, 150)){}
  while (!servo[3].MoveTo(80, 150)){}
}

void rise() {
  while (!servo[0].MoveTo(107, 100)){}
  while (!servo[1].MoveTo(0, 100)){}
  while (!servo[2].MoveTo(180, 100)){}
  while (!servo[3].MoveTo(0, 100)){}
  while (!servo[1].MoveTo(70, 50)) {}
  while (!servo[1].MoveTo(90, 50) &&
         !servo[2].MoveTo(140, 100)&&
         !servo[3].MoveTo(45, 100)){}
  while (!servo[3].MoveTo(90, 100)){}
}

void goDown(){
  while (!servo[0].MoveTo(107, 100)){}
  while (!servo[3].MoveTo(0, 100)){}
  while (!servo[2].MoveTo(180, 100)){}
  while (!servo[1].MoveTo(20, 50)){}
  while (!servo[1].MoveTo(0, 50) &&
         !servo[2].MoveTo(142, 100) &&
         !servo[3].MoveTo(80, 200)) {}
  rest();
}

void lookOut(){
  int s0 = random()%180;
  while (!servo[0].MoveTo(s0, 100)){}
  int lean = random()%30;
  while (!servo[1].MoveTo(90-lean, 50) &&
         !servo[2].MoveTo(140 - lean, 50)){}
  delay(1000);
  int tilt = (random()%90) + 45;
  while (!servo[3].MoveTo(tilt, 20)){}
  delay(700);
  while (!servo[3].MoveTo(90, 200)){}
}
