import processing.serial.*;

Serial myPort;  // Create object from Serial class

int val[] = {50,0,142,80};

void setup() 
{
  rectMode(CORNERS); 
  size(720, 720);
  background(0);
  stroke(255);
  for(int i = 0; i < 180; i += 10){
    line(0, height/180. * i, width,height/180. * i);
  }
  for(int i = 0; i < 4; i++){
    line(width/4. * i, 0, width/4 * i, height);
  }
  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  //printArray(Serial.list());
}

void draw() {
  background(0);
  stroke(255);
  
  fill(0,100,255);
  rect(0,0,width/4,val[0]*4);
  
  fill(0,255,100);
  rect(width/4,0,2*(width/4),val[1]*4);
  
  fill(100,0,100);
  rect(2*(width/4),0,3*(width/4),val[2]*4);
  
  fill(255,100,0);
  rect(3*(width/4),0,width,val[3]*4);
  
  for(int i = 0; i < 180; i += 10){
    line(0, height/180. * i, width,height/180. * i);
  }
  for(int i = 0; i < 4; i++){
    line(width/4. * i, 0, width/4 * i, height);
  }
  
  if(mousePressed){
    if(mouseX < width/4){
      val[0] = mouseY/4;
    }
    else if(mouseX < 2*(width/4)){
      val[1] = mouseY/4;
    }
    else if(mouseX < 3*(width/4)){
      val[2] = mouseY/4;
    }
    else if(mouseX < 4*(width/4)){
      val[3] = mouseY/4;
    }
    
    String values = "x" + str(val[0]) + "," + str(val[1]) + "," + str(val[2]) + "," + str(val[3]);
    println(values);
    myPort.write(values);
  }
}