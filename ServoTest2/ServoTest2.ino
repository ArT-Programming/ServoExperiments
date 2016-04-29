
#include <Servo.h>
#include <NewPing.h>

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



#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo myservo, servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos, pos2 = 0;    // variable to store the servo position
int aim, aim2;
int button = 8;
int count = 0;

unsigned long currentTime, previousTime, previousTime2 = 0;

void setup()
{
  pinMode(button,INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  servo.attach(10);
  aim = random() % 180;
  aim2 = random() % 180;

  servo.write(aim);
  myservo.write(aim2);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(button) || sonar.ping_cm() != 0){
     aim = random()%180;
     aim2 = random()%180;

   }
 
  previousTime = gotoPos(myservo, aim, previousTime);
  previousTime2 = gotoPos(servo, aim2, previousTime2);
//s 15ms for the servo to reach the position

}



