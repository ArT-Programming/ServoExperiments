#include "Arduino.h"
#include "NAservoChip.h"

NAservoChip::NAservoChip(){
    pos = 0;
    minimum = 0;
    maximum = 180;
}
  
void NAservoChip::Setup(int _channel, int _min, int _max){
    channel = _channel;
	minimum = _min;
	maximum = _max;
	clip(minimum, 0, 180);
	clip(maximum, 0, 180);
}
  
void NAservoChip::MoveTo(int _toPos){
	//clip(_toPos, minimum, maximum);
	pos = map(_toPos, 0, 180, minimum, maximum);
	CRCArduinoSerialServos::writeMicroseconds(channel, pos*10);
}
  
bool NAservoChip::MoveTo(int _toPos, int _velocity){
	 _toPos = map(_toPos, 0, 180, minimum, maximum);
	
	if(pos == _toPos){ return true; }
	
	int timeBetweenSteps = 1000 / _velocity;

	if(millis() > lastStepTime + timeBetweenSteps){
			if(pos > _toPos)	{ pos--; }
			else if(pos < _toPos){ pos++; }
		CRCArduinoSerialServos::writeMicroseconds(channel, pos*10);
		lastStepTime = millis();
	}

	if(pos == _toPos){ return true; }
	else{ return false; }
}

void NAservoChip::clip(int &_in, int _min, int _max){
	if(_in < _min) 		_in = _min;
	else if(_in > _max) _in = _max;
}