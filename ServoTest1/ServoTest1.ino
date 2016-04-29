/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/


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


Servo myservo, servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos, pos2 = 0;    // variable to store the servo position
int aim, aim2;
int button = 12;
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
  if(digitalRead(button)){
     aim = random()%180;
     aim2 = random()%180;

   }
  
  previousTime = gotoPos(myservo, aim, previousTime);
  previousTime2 = gotoPos(servo, aim2, previousTime2);

  //aim = count % 2 * 180;
  //count++;
 
 /* myservo.write(aim);
  pos = myservo.read();

  Serial.print("aim ");
  Serial.print(aim);
  Serial.print("   pos ");
  Serial.println(pos);
  delay(750);
   if(pos == aim){
     aim = random()%180;
     myservo.write(aim);
   }
   pos2 = servo.read();
   if(pos2 == aim2){
     aim2 = random()%180;
     servo.write(aim2);
   }
   */
  //delay(200);

  /*pos = random() % 180;                              // in steps of 1 degree
    myservo.write(pos);      // tell servo to go to position in variable 'pos'
    delay(random() % 700 + 250 );
    pos = random() % 180;
    servo.write(pos);
    delay(random() % 700 + 250); */                     // waits 15ms for the servo to reach the position

}



