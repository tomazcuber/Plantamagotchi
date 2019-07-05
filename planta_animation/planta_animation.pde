import processing.serial.*;

Serial myPort;
Animation animation_feliz, animation_triste;

float xpos;
float ypos;
boolean isHappy; 

void setup() {
  size(640, 360);
  background(255, 204, 0);
  frameRate(12);
  
  myPort = new Serial(this, Serial.list()[0],9600);
  myPort.bufferUntil('\n');
  
  animation_feliz = new Animation("Planta_Feliz_", 37);
  animation_triste = new Animation("Planta_Triste_", 34);
  ypos = height * 0.25;
  xpos = width * 0.5;
}

void serialEvent(Serial myPort){
  String boolString = myPort.readStringUntil('\n');
  isHappy = boolean(boolString);
}

void draw() { 
  

  // Display the sprite at the position xpos, ypos
  if(isHappy){
    background(139, 0, 0);
    animation_triste.display(xpos-animation_triste.getWidth()/2, ypos);
  } else {    
    background(238, 0, 0);
    animation_feliz.display(xpos-animation_feliz.getWidth()/2, ypos);
  }
}
