
#include <Servo.h>

unsigned long gotoPos(Servo s, int wantedPos, unsigned long lastSet, int betweenDegrees = 15) {
  int readPos = s.read();
  if (millis() > lastSet + betweenDegrees)
  {
    if (readPos > wantedPos) {
      readPos--;
      s.write(readPos);
      lastSet = millis();
    }
    if (readPos < wantedPos) {
      readPos++;
      s.write(readPos);
      lastSet = millis();
    }
  }
  return lastSet;
}
Servo servo, servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos, pos2 = 0;    // variable to store the servo position
int aim, aim2;
int button = 8;
int count = 0;
int delayTime = 250;

unsigned long currentTime, previousTime, previousTime2 = 0;

void setup()
{
  pinMode(button,INPUT);
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);
  aim = 0;
  aim2 = 90;

  servo.write(aim);
  servo2.write(aim2);
  Serial.begin(9600);
}

void loop()
{
  servo.write(0);
  delay(delayTime+100);
  servo2.write(120);
  delay(delayTime-100);
  servo.write(10);
  delay(delayTime);
  servo2.write(150);
  delay(delayTime);
  servo.write(20);
  delay(delayTime);
  servo2.write(60);
  delay(delayTime);
  servo.write(30);
  delay(delayTime);
  servo2.write(90);
  delay(delayTime);
}



