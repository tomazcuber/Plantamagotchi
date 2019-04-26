import processing.serial.*;

Serial myPort;
float backgroundColor_blue;
float backgroundColor_red;

void setup(){
  size(500,500);
  
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  
}

void serialEvent(Serial myPort){
  String colorsString = myPort.readStringUntil('\n');
  int commaIndex= colorsString.indexOf(",");
 
  backgroundColor_blue = float(colorsString.substring(0, commaIndex));
  println("B: " + backgroundColor_blue);
  
  backgroundColor_red = float(colorsString.substring(commaIndex+1));
  println("R: " + backgroundColor_red);
}

void draw(){
  background(backgroundColor_red, backgroundColor_blue, 150 );
  
  if(mousePressed && (mouseButton == LEFT)){
    myPort.write('1');
  }
  
  if(mousePressed && (mouseButton == RIGHT)){
    myPort.write('0');
  }
}  
  
