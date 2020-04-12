#include <ArduinoJson.h>

int resval = 0;  // holds the value
int respin_A5 = A5; // sensor pin used
char device_uuid [8] = "ef3zf67";


 
void setup() { 
 
  // start the serial console
  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  //all other "init" code goes here as well
}

//take a ph level reading
float ph() {
  //resval = digitRead(respin_A6);
  //return resval
  float ph = random(5.62,6.11);
  return ph;
}

// take a reading from the temp sensor
float temp() {
  float temp = random(20.01,28.99);
  return temp;
}

//take a reading from the humidity sensor
int humidity() { 
  int humidity = random(45,69);
  //if possible then humidity reported separatetly with this method
  return humidity;
}

//take a reading from the water-level sensor
int water_level() {
 //take reading from analog pin and store it to resval variable
 resval = analogRead(respin_A5);
 if (resval<=100){
   Serial.println("Water Level: Empty");
 } else if (resval>100 && resval<=300){
   Serial.println("Water Level: Low");
 } else if (resval>300 && resval<=330){
   Serial.println("Water Level: Medium");
 } else if (resval>330){
   Serial.println("Water Level: High");
 }
 return resval;
}
  
//the infinite loop of sensor reading
void loop() { 

  //will be sent to topic: 37e781d9d23260a2a66b7fe7b638e314df/sensor
  Serial.println(); 
  //clear buffer and init json
  
const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
DynamicJsonDocument doc(capacity);

doc["device"] = device_uuid;
doc["time"] = "20-18-04T11:24:36Z";

JsonArray data = doc.createNestedArray("data");

JsonObject data_0 = data.createNestedObject();
data_0["temp"] = temp();
data_0["humidity"] = humidity();
data_0["water"] = 330;
data_0["ph"] = ph();
data_0["ldr"] = 485;

serializeJson(doc, Serial);

  //take reading from water level sensor and print to console
  //Serial.println(temp());
  delay(8000);
  //temp_sensor()
  //delay(8000);
  //humidity_sensor();
  //delay(8000);
}
