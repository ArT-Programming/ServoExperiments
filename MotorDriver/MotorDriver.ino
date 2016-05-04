class MotorDriver
{
  int enablePin, forwardsPin, backwardsPin;
public:
  MotorDriver(int _enable, int _forwards, int _backwards){
    enablePin = _enable;
    forwardsPin = _forwards;
    backwardsPin = _backwards;
    pinMode(enablePin, OUTPUT);
    pinMode(forwardsPin, OUTPUT);
    pinMode(backwardsPin, OUTPUT);
  }
  
  void goForwards(int Speed){
    digitalWrite(forwardsPin, HIGH);
    digitalWrite(backwardsPin, LOW);
    analogWrite(enablePin, Speed);
  }
  
  void goBackwards(int Speed){
    digitalWrite(forwardsPin, LOW);
    digitalWrite(backwardsPin, HIGH);
    analogWrite(enablePin, Speed);
  }
  
  void STOP(){
    digitalWrite(forwardsPin, LOW);
    digitalWrite(backwardsPin, LOW);
    analogWrite(enablePin, 0);
  }
};

MotorDriver arm(5,6,7);
MotorDriver rotation(9,10,11);

void setup() {
  
}

void loop() {
  rotation.goForwards(50);
  arm.goBackwards(255);
  delay(10000);
  
  rotation.STOP();
  arm.STOP();
  delay(1000);
  
  rotation.goBackwards(50);
  arm.goForwards(255);
  delay(10000);
  
  rotation.STOP();
  arm.STOP();
  delay(1000);
}
