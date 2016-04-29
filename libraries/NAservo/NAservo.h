#ifndef NAservo_h
#define NAservo_h

#include "Arduino.h"
#include <Servo.h>

class NAservo : public Servo::Servo{
public:
  Servo motor;
  int pos;
  int minimum, maximum;
  unsigned long lastStepTime;
  
  NAservo();
  void Setup(int _pin, int _min, int _max);
  void MoveTo(int _toPos);
  bool MoveTo(int _toPos, int _velocity);
  void clip(int &_in, int _min, int _max);
};

#endif