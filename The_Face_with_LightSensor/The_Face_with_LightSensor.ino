#include <Servo.h>
#include <NAservo.h>

NAservo servo[4];
int lightSensor = 0;
int scanValues[360];

void setup()
{
  pinMode(12, OUTPUT);
  
  servo[0].Setup(3, 0, 180);
  servo[1].Setup(5, 0, 180);
  servo[2].Setup(6, 0, 180);
  servo[3].Setup(9, 0, 180);

  Serial.begin(9600);
  servo[0].MoveTo(0);
  servo[1].MoveTo(90);
  servo[2].MoveTo(140);
  servo[3].MoveTo(90);
  delay(1000);
}

void loop()
{
  delay(2000);
  scan();
}

void scan() {
  while (!servo[2].MoveTo(140 , 120)) {}
  for (int i = 0; i < 180; i++) {
    while (!servo[0].MoveTo(i, 120)) {}
    scanValues[i] = analogRead(lightSensor);
   /* Serial.print(i);
    Serial.print(": ");
    Serial.print(scanValues[i]);
    Serial.print(";   ");*/
  }
  
  while (!servo[2].MoveTo(0 , 120)) {}
  for (int i = 179; i >= 0; i--) {
    while (!servo[0].MoveTo(i, 120)) {}
    scanValues[i+180] = analogRead(lightSensor);
   /* Serial.print(i+11);
    Serial.print(": ");
    Serial.print(scanValues[i]);
    Serial.print(";   ");*/
  }

  Serial.println();

  int brightest = 0;
  for (int i = 0; i < 360; i++) {
    if (scanValues[i] > brightest) {
      brightest = scanValues[i];
    }
  }

  //Serial.print("Brightest: ");
  //Serial.println(brightest);

  for (int i = 0; i < 360; i++) {
    if (scanValues[i] == brightest) {
      if(i < 180){
        while (!servo[2].MoveTo(140 , 120)) {}
        while (!servo[0].MoveTo(i, 120)) {}
      }else{
        while (!servo[2].MoveTo(0 , 120)) {}
        while (!servo[0].MoveTo(i-180, 120)) {}
      }
      break;
    }
  }

  digitalWrite(12,HIGH);
  delay(200);
  digitalWrite(12,LOW);
  delay(200);
  digitalWrite(12,HIGH);
  delay(200);
  digitalWrite(12,LOW);
  delay(200);
  digitalWrite(12,HIGH);
  delay(200);
  digitalWrite(12,LOW);
  delay(200);
  //nod();
}

void nod() {
  while (!servo[2].MoveTo(180, 100)) {}
  while (!servo[2].MoveTo(140, 100)) {}
  while (!servo[2].MoveTo(180, 100)) {}
  while (!servo[2].MoveTo(140, 100)) {}
}

void rest() {
  while (!servo[0].MoveTo(50, 150)) {}
  while (!servo[1].MoveTo(0, 150)) {}
  while (!servo[2].MoveTo(142, 150)) {}
  while (!servo[3].MoveTo(80, 150)) {}
}

void rise() {
  while (!servo[0].MoveTo(107, 100)) {}
  while (!servo[1].MoveTo(0, 100)) {}
  while (!servo[2].MoveTo(180, 100)) {}
  while (!servo[3].MoveTo(0, 100)) {}
  while (!servo[1].MoveTo(70, 50)) {}
  while (!servo[1].MoveTo(90, 50) &&
         !servo[2].MoveTo(140, 100) &&
         !servo[3].MoveTo(45, 100)) {}
  while (!servo[3].MoveTo(90, 100)) {}
}

void goDown() {
  while (!servo[0].MoveTo(107, 100)) {}
  while (!servo[3].MoveTo(0, 100)) {}
  while (!servo[2].MoveTo(180, 100)) {}
  while (!servo[1].MoveTo(20, 50)) {}
  while (!servo[1].MoveTo(0, 50) &&
         !servo[2].MoveTo(142, 100) &&
         !servo[3].MoveTo(80, 200)) {}
  rest();
}

void lookOut() {
  int s0 = random() % 180;
  while (!servo[0].MoveTo(s0, 100)) {}
  int lean = random() % 30;
  while (!servo[1].MoveTo(90 - lean, 50) &&
         !servo[2].MoveTo(140 - lean, 50)) {}
  delay(1000);
  int tilt = (random() % 90) + 45;
  while (!servo[3].MoveTo(tilt, 20)) {}
  delay(700);
  while (!servo[3].MoveTo(90, 200)) {}
}
