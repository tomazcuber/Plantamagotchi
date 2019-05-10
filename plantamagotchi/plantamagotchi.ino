#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 3
#define SOILPIN A0
#define LIGHTPIN A1
#define LEDPIN 13
#define DHTTYPE DHT11

int minSoilMoisture = 200;
int maxSoilMoisture = 600;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(LIGHTPIN, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial){
    delay(200);
  }
  
  dht.begin();
}

void loop() {
  float airTemperature;
  float airHumidity;
  float heatIndex;
  int light;
  int soilMoisture;
  bool validAirConditions;
   
  if(Serial.available() > 0){
    char state = Serial.read();
    if (state == '1'){
      digitalWrite(LEDPIN, HIGH); 
    }
    if(state == '0'){
      digitalWrite(LEDPIN, LOW);
    }    
  }
  validAirConditions = getAirConditions(&airTemperature, &airHumidity, &heatIndex);
  if( !validAirConditions ){
    return;
  }
  soilMoisture = getSoilMoisture();
  light = getLight();
  Serial.println(String("SOIL MOISTURE: ") + soilMoisture + String("\tLIGHT: ") + light + String("\tTEMPURATURE: ") + airTemperature + String("\tHUMIDITY: ") + airHumidity + String("\tHEAT INDEX: ") + heatIndex);

  delay(1000);
}

bool getAirConditions(float *temperature, float *humidity, float *heatIndex){
  *temperature = dht.readTemperature();
  *humidity = dht.readHumidity();
  bool ret = true;
  if (isnan(*temperature) || isnan(*humidity)){
    ret = false;
  }
  *heatIndex = dht.computeHeatIndex(*temperature, *humidity, false);
  return ret;
}

int getLight(){
  int rawLightSensor = analogRead(LIGHTPIN);
  return rawLightSensor;
}

int getSoilMoisture(){
  int soilSensorOutput = analogRead(SOILPIN);
  return map(constrain(soilSensorOutput, minSoilMoisture, maxSoilMoisture), minSoilMoisture, maxSoilMoisture, 0, 255);
}
