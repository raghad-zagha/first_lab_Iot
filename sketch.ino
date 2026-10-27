// Channel ID :3554205
// API key : QSFALVR8B3EBLY5V


#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"


const char* WIFI_Name = "Wokwi-GUEST";
const char* WIFI_Pass = "";


const int channelNumber = 3554205;
const char* apiKey = "QSFALVR8B3EBLY5V";

const char* universityID = "12218926";


#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient clientObject;


void setup() {

  pinMode(DHTPIN, INPUT);

  Serial.begin(115200);

  
  WiFi.mode(WIFI_STA);

  
  WiFi.begin(WIFI_Name, WIFI_Pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Status: Not Connected");
    delay(1000);
  }

  Serial.println("Status: Connected");

  
  dht.begin();

  ThingSpeak.begin(clientObject);

  Serial.print("University ID: ");
  Serial.println(universityID);
}

void loop() {

 
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Failed to read from DHT sensor");
    delay(20000);
    return;
  }

  Serial.println("----------------------");

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("University ID: ");
  Serial.println(universityID);

 
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  int stat = ThingSpeak.writeFields(channelNumber, apiKey);

  if (stat == 200)
  {
    Serial.println("Data Sent to ThingSpeak");
  }
  else
  {
    Serial.print("Problem sending data. HTTP error code: ");
    Serial.println(stat);
  }

  
  delay(20000);
}
