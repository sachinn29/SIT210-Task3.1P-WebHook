#include <SPI.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>


const char *ssid = "Galaxy";
const char *password = "sachin123";
const char *write_api_key = "NA8IS24DG717O8L1";
const int ldrPin = A0;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  ThingSpeak.setField(1, ldrValue); // Set the value to send to Field 1

  int httpCode = ThingSpeak.writeFields(2250648, write_api_key); 

  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.println("Error sending data to ThingSpeak.");
  }

  delay(30000); // Send data every 30 seconds
}
