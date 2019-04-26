int ledPin = 7;
int dialPin = A0;
int dialOutput;

int sensorPin = A1;
int sensorOutput;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  dialOutput = analogRead(dialPin);
  sensorOutput = analogRead(sensorPin);

  
  int mappedSensorOutput = map(constrain(sensorOutput, 200, 600), 200, 600, 0, 255);
  int mappedDialOutput = map(dialOutput, 0, 1023, 0, 255);

  Serial.println(mappedSensorOutput +  String(",") + mappedDialOutput);
  
  
  if(Serial.available() > 0){
    char state = Serial.read();
    if (state == '1'){
      digitalWrite(ledPin, HIGH); 
    }
    if(state == '0'){
      digitalWrite(ledPin, LOW);
    }

    
  }

  
  //delay(1000);
}
