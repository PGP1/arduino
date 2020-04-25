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

int control_command(char* instruction) {
  int command = 0;

  if 
  return command;
}
  
//the infinite loop of sensor reading
void loop() { 

//listen to topic

const size_t capacity = JSON_ARRAY_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + 40;
DynamicJsonDocument doc(capacity);

const char* json = Serial.read(); 

deserializeJson(doc, json);

const char* sensor = doc["controller"]; // "topic"

JsonObject data_0 = doc["data"][0];
int data_0_fan = data_0["fan"]; // 1
int data_0_light = data_0["light"]; // 486
int data_0_pump = data_0["pump"]; // 330

instruction = reciever();


if command(instruction) == 1 {
  fan();
}

else if command(instruction) == 2 {
  pump();
}
// otherwise it must be a light instruction
else if command(instruction) == 3{
  int ldr = 0
  (int)instruction.ldr = int ldr;
  light(ldr);
} 
else {
Serial.println("Error, command not recognised");
{

delay(8000);
}
