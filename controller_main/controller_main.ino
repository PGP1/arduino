#include <ArduinoJson.h>
#include "DHT.h"
#define PHANALOGPIN A0
#define DHTDIGITALPIN 7
#define DHTTYPE DHT11
#define WATERLEVELANALOGPIN A1
#define LEDPOWER 11
#define WATERLEVELPOWER 5

DHT dht(DHTDIGITALPIN, DHTTYPE);

unsigned long int avgValue;
float b;
int buf[10], temporary;

int waterLevelResval = 0; // holds the value
char deviceUUID[8] = "ef3zf67";

int brightness = 0;
int fadeAmount = 5;

void setup()
{

  // start the serial connnection
  Serial.begin(9600);

  //mock data generation
  randomSeed(analogRead(0));

  // setup pin to communicate to sensors
  pinMode(LEDPOWER, OUTPUT);
  pinMode(WATERLEVELPOWER, OUTPUT);
	
  // Supply power to water level sensor
  digitalWrite(WATERLEVELPOWER, HIGH);

  // setup dht sensor
  dht.begin();
}

//take a ph level reading
float ph()
{

  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(PHANALOGPIN);
    delay(10);
  }

  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temporary = buf[i];
        buf[i] = buf[j];
        buf[j] = temporary;
      }
    }
  }
  avgValue = 0;

  for (int i = 2; i < 8; i++)
  {
    avgValue += buf[i];
  }

  float phValue = (float)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  phValue = 3.5 * phValue;                          //convert the millivolt into pH value
  
  // Mock Data
  // resval = digitRead(respin_A6);
  // return resval
  // float ph = random(5.62,6.11);
  // return ph;

  return phValue;
}

// take a reading from the temp sensor
float temp()
{
  // Mock Data
  // float temp = random(20.01,28.99);
  // return temp;
  float temp = dht.readTemperature();
  return temp;
}

//take a reading from the humidity sensor
int humidity()
{
  // Mock Data
  // int humidity = random(45,69);
  // if possible then humidity repeated separatetly with this method
  // return humidity;
  float humidity = dht.readHumidity();
  return humidity;
}

//take a reading from the water-level sensor
int waterLevel()
{
  //take reading from analog pin and store it to resval variable
  waterLevelResval = analogRead(WATERLEVELANALOGPIN);
  if (waterLevelResval <= 100)
  {
   // Serial.println("Water Level: Empty");
  }
  else if (waterLevelResval > 100 && waterLevelResval <= 300)
  {
   // Serial.println("Water Level: Low");
  }
  else if (waterLevelResval > 300 && waterLevelResval <= 330)
  {
   // Serial.println("Water Level: Medium");
  }
  else if (waterLevelResval > 330)
  {
   // Serial.println("Water Level: High");
  }
  return waterLevelResval;
}

String parsePayload()
{
  String data;
  if (Serial.available() > 0)
  {
    data = Serial.readStringUntil('\n');
  }
  return data;
}

int changeLightBrightness(int *frequency)
{
  analogWrite(LEDPOWER, frequency);
  brightness = frequency;

}

int getBrightness(){

  return brightness;
}

void sensorData()
{
  Serial.println();
  //clear buffer and init json
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
  DynamicJsonDocument doc(capacity);

  doc["device"] = deviceUUID;
  JsonObject data = doc.createNestedObject("data");

  data["temp"] = temp();
  data["humidity"] = humidity();
  data["water"] = waterLevel();
  data["ph"] = ph();
  data["ldr"] = getBrightness();

  serializeJson(doc, Serial);
  delay(60000);
}

void receiver()
{
  String payload;
  //listen to topic
  if (Serial.available())
  {
    const size_t capacity = JSON_ARRAY_SIZE(1) + 2 * JSON_OBJECT_SIZE(3) + 40;
    DynamicJsonDocument doc(capacity);
    payload = parsePayload();
    DeserializationError err = deserializeJson(doc, payload);

    int data_0_light = doc["controller"]["light"].as<int>();
    int data_0_fan = doc["controller"]["fan"].as<int>();
    int data_0_pump = doc["controller"]["pump"].as<int>();

    if (data_0_light >= 0)
    {
      Serial.println("Arduino [DEBUG]:{\"Success\":\"True\"}");
      changeLightBrightness(data_0_light);
    }
    else if (data_0_pump == 1)
    {
    }
    else if (data_0_fan == 1)
    {
    }
    else
    {
     // Serial.print("Arduino [DEBUG]: deserializeJson() returned ");
     // Serial.println(err.c_str());

      while (Serial.available() > 0)
      {
        Serial.read();
      }
    }
  }
}

//the infinite loop of sensor reading
void loop()
{
  sensorData();
  receiver();
}
