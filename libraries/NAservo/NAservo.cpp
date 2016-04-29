#include "Arduino.h"
#include "NAservo.h"

NAservo::NAservo(){
    pos = 0;
    minimum = 0;
    maximum = 180;
}
  
void NAservo::Setup(int _pin, int _min, int _max){
    motor.attach(_pin);
	minimum = _min;
	maximum = _max;
	clip(minimum, 0, 180);
	clip(maximum, 0, 180);
}
  
void NAservo::MoveTo(int _toPos){
	//clip(_toPos, minimum, maximum);
	pos = map(_toPos, 0, 100, minimum, maximum);
	motor.write(pos);
}
  
bool NAservo::MoveTo(int _toPos, int _velocity){
	 _toPos = map(_toPos, 0, 100, minimum, maximum);
	
	if(pos == _toPos){ return true; }
	
	int timeBetweenSteps = 1000 / _velocity;

	if(millis() > lastStepTime + timeBetweenSteps){
			if(pos > _toPos)	{ pos--; }
			else if(pos < _toPos){ pos++; }
		motor.write(pos);
		lastStepTime = millis();
	}

	if(pos == _toPos){ return true; }
	else{ return false; }
}

void NAservo::clip(int &_in, int _min, int _max){
	if(_in < _min) 		_in = _min;
	else if(_in > _max) _in = _max;
}