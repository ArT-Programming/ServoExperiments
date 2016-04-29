#ifndef NAservo_h
#define NAservo_h

#include "Arduino.h"
#include "RCArduinoSerialServosLocal.h"

class NAservoChip{
public:
  int pos;
  int channel;
  int minimum, maximum;
  unsigned long lastStepTime;
  
  NAservoChip();
  void Setup(int _channel, int _min, int _max);
  void MoveTo(int _toPos);
  bool MoveTo(int _toPos, int _velocity);
  void clip(int &_in, int _min, int _max);
};

#endif