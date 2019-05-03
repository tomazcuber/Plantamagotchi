#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 3
#define DHTTYPE DHT11
#define SOILPIN A0
#define LEDPIN 13

int soilMoistureSensorOutput;

float airTemperature;
float airMoisture;

int soilMoisture;
int minSoilMoisture = 200;
int maxSoilMoisture = 600;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LEDPIN, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial){
    delay(200);
  }
  
  dht.begin();
 
}

void loop() {
  
  soilMoisture = getSoilMoisture();
  Serial.println(soilMoisture);
   
  if(Serial.available() > 0){
    char state = Serial.read();
    if (state == '1'){
      digitalWrite(LEDPIN, HIGH); 
    }
    if(state == '0'){
      digitalWrite(LEDPIN, LOW);
    }

    
  }

  
  //delay(1000);
}

int getSoilMoisture(){
  int soilSensorOutput = analogRead(SOILPIN);
  return map(constrain(soilSensorOutput, minSoilMoisture, maxSoilMoisture), minSoilMoisture, maxSoilMoisture, 0, 255);
}
