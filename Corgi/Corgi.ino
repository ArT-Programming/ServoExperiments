#include <Servo.h>
#include <NAservo.h>

class Corgi{
public:
  NAservo leg[4];

  Corgi(){  
  }

  void Setup(){
    //Setup legs (pin, min, max) - The min and max values are related to the height of the leg, not the angle of the motor.
    leg[0].Setup(3,160,0);
    leg[1].Setup(5,0,160);
    leg[2].Setup(6,0,160);
    leg[3].Setup(9,160,0);
  }

  void FastJump(){
    leg[0].MoveTo(10);
    leg[1].MoveTo(10);
    leg[2].MoveTo(0);
    leg[3].MoveTo(0);
    delay(50);
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(20);
    leg[3].MoveTo(20);
    delay(100);
  }
  void SlowJump(){
    leg[0].MoveTo(30);
    leg[1].MoveTo(30);
    leg[2].MoveTo(0);
    leg[3].MoveTo(0);
    delay(100);
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(40);
    leg[3].MoveTo(40);
    delay(200);
  }
  void FromLegToLeg(){
    leg[0].MoveTo(10);
    leg[1].MoveTo(10);
    leg[2].MoveTo(40);
    leg[3].MoveTo(10);
    delay(100);
    leg[0].MoveTo(10);
    leg[1].MoveTo(10);
    leg[2].MoveTo(10);
    leg[3].MoveTo(40);
    delay(100);
  }

  void Jump(){
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(0);
    leg[3].MoveTo(0);
    delay(10); 
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(20);
    leg[3].MoveTo(20);
    delay(20);
    leg[0].MoveTo(40);
    leg[1].MoveTo(40);
    leg[2].MoveTo(30);
    leg[3].MoveTo(30);
    delay(20);
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(0);
    leg[3].MoveTo(0);
    delay(250);
  }

  void ShakeIt(){
    leg[0].MoveTo(0);
    leg[1].MoveTo(0);
    leg[2].MoveTo(0);
    leg[3].MoveTo(0);
    delay(10); 
    leg[0].MoveTo(20);
    leg[1].MoveTo(20);
    leg[2].MoveTo(20);
    leg[3].MoveTo(20);
    delay(10);
    leg[0].MoveTo(40);
    leg[1].MoveTo(40);
    leg[2].MoveTo(40);
    leg[3].MoveTo(40);
    delay(10);
    leg[0].MoveTo(20);
    leg[1].MoveTo(20);
    leg[2].MoveTo(20);
    leg[3].MoveTo(20);
    delay(10);
  }


  void LevelOut(int input){
    for(int i = 0; i < 4; i++){
      leg[i].MoveTo(input);
    }
    delay(1000);
  }

  void LookOut(){
    while(!leg[0].MoveTo(100, 200) &&
      !leg[1].MoveTo(100, 200) &&
      !leg[2].MoveTo(100, 200) &&
      !leg[3].MoveTo(100, 200)){
    }
    delay(random()%500 + 1500);
    //LiftLeg(1, 100, 80);
    //delay(300);
    while(!leg[0].MoveTo(0, 50) &&
      !leg[1].MoveTo(0, 50) &&
      !leg[2].MoveTo(0, 50) &&
      !leg[3].MoveTo(0, 50)){
    }
    delay(200);
  }

  void LiftLeg(int index, int a, int b){
    while(!leg[0].MoveTo(b, 40) &&
      !leg[1].MoveTo(b, 40)){
    }
    delay(200);
    while(!leg[0].MoveTo(a, 40) &&
      !leg[1].MoveTo(a, 40)){
    }
  }
};

Corgi corgi;
unsigned long lastLookOutTime = 0;
int waitTime = 5000;
int count = 0;
void setup()
{
  corgi.Setup();
}

void loop()
{


  if(millis() > lastLookOutTime + waitTime){
    corgi.LevelOut(20);
    corgi.LookOut();
    lastLookOutTime = millis();
    waitTime = random() % 5000 + 5000;
    count++;
    if(count > 5) count = 0;
  } 
  else{
    switch(count){
    case 0:  
      corgi.FastJump();
      break;
    case 1:
      corgi.SlowJump();
      break;
    case 2:
      corgi.Jump();
      break;
    case 3:
      corgi.FromLegToLeg();
      break;
    case 4:
      corgi.ShakeIt();
      break;
    default:

      break;
    }
  }
  /*for(int i = 0; i <= 10; i++){
   for(int m = 0; m < 4; m++){
   leg[m].MoveTo(i*10);
   }
   delay(500);
   }
   
   for(int i = 10; i <= 0; i--){
   for(int m = 0; m < 4; m++){
   leg[m].MoveTo(i*10);
   }
   delay(500);
   }*/

  /*
  while(!leg[0].MoveTo(0, 50) &&
   !leg[1].MoveTo(0, 50) &&
   !leg[2].MoveTo(0, 50) &&
   !leg[3].MoveTo(0, 50)){}
   
   //delay(500);
   
   leg[0].MoveTo(100);
   leg[1].MoveTo(100);
   leg[2].MoveTo(100);
   leg[3].MoveTo(100);
   
   delay(1000);*/
}



