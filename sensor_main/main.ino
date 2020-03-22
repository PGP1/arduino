int resval = 0;  // holds the value
int respin_A5 = A5; // sensor pin used
  
void setup() { 
 
  // start the serial console
  Serial.begin(9600);

  //all other "init" code goes here as well
}

//take a ph level reading
int ph_level() {
  //resval = digitRead(respin_A6);
  //return resval
}

// take a reading from the temp sensor, best to use ints here because floats use more RAM
int temp() {
  int temp = 27;
  //code to return temp (and maybe humidity as both reported via single pin)
  return temp;
}

//take a reading from the humidity sensor
int humidity() { 
  int humidity = 69;
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
 return resvval;
}
  
//the infinite loop of sensor reading
void loop() { 
  //take reading from water level sensor and print to console
  water_level()
  delay(8000);
  //temp_sensor()
  //delay(8000);
  //humidity_sensor();
  //delay(8000);
}
