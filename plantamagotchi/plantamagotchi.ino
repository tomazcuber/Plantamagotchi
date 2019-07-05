#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>

#define DHTPIN 3
#define SOILPIN A0
#define LIGHTPIN A1
#define LEDPIN 13
#define DHTTYPE DHT11

int minSoilMoisture = 200;
int maxSoilMoisture = 600;

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(LIGHTPIN, OUTPUT);
  
  Wire.begin();
  lightMeter.begin();
  
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
  float light;
  int soilMoisture;
  bool validAirConditions;
  bool plantHappy;

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
  plantHappy = isPlantHappy(airTemperature,soilMoisture);
  Serial.println(plantHappy);
  
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

float getLight(){
  float rawLightSensor = lightMeter.readLightLevel();
  return rawLightSensor;
}

int getSoilMoisture(){
  int soilSensorOutput = analogRead(SOILPIN);
  //return map(constrain(soilSensorOutput, minSoilMoisture, maxSoilMoisture), minSoilMoisture, maxSoilMoisture, 0, 255);
  return soilSensorOutput;
}

bool isPlantHappy(float airTemperature, int soilMoisture){
  bool temperatureOk;
  bool soilMoistureOk;
  
  if (airTemperature >= 18.00 && airTemperature <= 32.00) temperatureOk = true;//Temperaturas mínimas e máximas para crescimento vegetativo de tomates (18º C & 32º C) 
  else temperatureOk = false;
  if(soilMoisture >= 170 && soilMoisture <= 220) soilMoistureOk = true; //Umidade resgistrada pelo sensor de um tomate encharcado (~170) e de um tomate com a terra seca (~220)
  else soilMoistureOk = false;
  
  if(soilMoistureOk && temperatureOk){
  return true;
  } else {
  return false;
  }
}
