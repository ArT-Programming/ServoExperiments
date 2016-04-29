// RCArduinoSerialServos by DuaneB is licensed under a Creative Commons Attribution-NonCommercial 3.0 Unported License.
// Based on a work at rcarduino.blogspot.com.
#include "RCArduinoSerialServosLocal.h"

int pos = 1000;
int dir = 1;
int moveby = 200;

int c = 0;
int count = 0;
int channel[8] = {0, 1, 2, 3, 10, 11, 12, 13};

void setup()
{
  Serial.begin(9600);

  setupServos();
}

void loop()
{
  //if (count < 8) randomRound();
  //else pulseAll();
  
  //* Processing Control
  if (Serial.find("x")) {
    int value[8];
    for(int i = 0; i < 8; i++){
      value[i] = Serial.parseInt();
      setServo(channel[i], value[i]*10);
    }
  }
  //*/
}

//************
void randomRound() {
  setServo(channel[c], pos);

  c++;
  if (c == 8) {
    c = 0;
    count++;
    if (count < 8) {
      pos = random() % 1800;
    }
  }
  delay(200);
}

void pulseAll() {
  for (int i = 0; i < 8; i++) {
    setServo(channel[i], pos);
  }
  pos += (10 + (4 * (count - 8))) * dir;
  if (dir == 1 && pos >= 1800) {
    dir = -1;
    pos = 1800;
  }
  else if (dir == -1 && pos <= 0) {
    dir = 1;
    pos = 0;
    count++;
  }
  if (count > 12) count = 0;
  delay(10);
}

//***********
void setServo(int _channel, int _pos){
  CRCArduinoSerialServos::writeMicroseconds(_channel, _pos);
}

void setupServos(){
  // set the channels
  for (uint16_t nChannel = 0; nChannel < RCARDUINO_MAX_SERVOS; nChannel++)
  {
    setServo(nChannel, 900);
  }
  CRCArduinoSerialServos::begin();
}
