#include <ArduinoJson.h>

int resval = 0;  // holds the value
int respin_A5 = A5; // sensor pin used
char device_uuid [8] = "ef3zf67";

int led = 11;
int brightness = 0;
int fadeAmount = 5;

void setup() { 
 
  // start the serial console
  Serial.begin(9600);
  
  //mock data generation
  randomSeed(analogRead(0));
  
  // set up pin to communicate to sensors
  pinMode(led, OUTPUT);
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

String parsePayload() {
  String data;
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
  }
  return data;
}

int light(int* frequency) {
  analogWrite(led, frequency);
}

void mockData() {
  //will be sent to topic: 37e781d9d23260a2a66b7fe7b638e314df/sensor
  Serial.println(); 
  //clear buffer and init json
  
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
  DynamicJsonDocument doc(capacity);

  doc["device"] = device_uuid;
  JsonArray data = doc.createNestedArray("data");

  JsonObject data_0 = data.createNestedObject();
  data_0["temp"] = temp();
  data_0["humidity"] = humidity();
  data_0["water"] = 330;
  data_0["ph"] = ph();
  data_0["ldr"] = 485;

  serializeJson(doc, Serial);

  delay(8000);
}

void receiver(){
  String payload;
  //listen to topic
  if(Serial.available()) {
    const size_t capacity = JSON_ARRAY_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + 40;
    DynamicJsonDocument doc(capacity);
    payload = parsePayload();
    DeserializationError err = deserializeJson(doc, payload);
    
    int data_0_fan = doc["controller"]["fan"].as<int>();
    int data_0_light = doc["controller"]["light"].as<int>();
    int data_0_pump = doc["controller"]["pump"].as<int>();

    if(data_0_light >= 0) {
      Serial.println("Arduino [DEBUG]:{\"Success\":\"True\"}");
      light(data_0_light);    
    }
    else if(data_0_pump == 1) {
      
    }
    else if(data_0_fan == 1) {
  
    }
    else {
      Serial.print("Arduino [DEBUG]: deserializeJson() returned ");
      Serial.println(err.c_str());

      while(Serial.available() > 0) {
        Serial.read();
      }
    }
  }
}

//the infinite loop of sensor reading
void loop() { 
  receiver();
  delay(8000);
}
