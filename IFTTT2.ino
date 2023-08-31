#include <BH1750.h>               // To include the BH1750 library
#include <Wire.h>                  //To include the Wire library for I2C communication
#include "thingProperties.h"       // To include the thingProperties.h file for Arduino IoT Cloud properties
#include <ArduinoIoTCloud.h>       // To include the Arduino IoT Cloud library
#include <Arduino_ConnectionHandler.h>

BH1750 LightSensor;               // To create an instance of the BH1750 class for the light sensor

void setup() {
  Serial.begin(9600);            // For starting serial communication for debugging
  Wire.begin();                  // To initialize the I2C communication
  LightSensor.begin();           // To initialize the light sensor
  initProperties();              // To initialize properties defined in thingProperties.h
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);  // To start Arduino IoT Cloud connection
  setDebugMessageLevel(2);       //To set debug message level
  ArduinoCloud.printDebugInfo();  //To print debug information for Arduino IoT Cloud
}

void loop() {
  ArduinoCloud.update();         //For updating the Arduino IoT Cloud connection

  float lux = LightSensor.readLightLevel();  //To read light level from the sensor
  intensity_light = lux;         //To store the light level in the intensity_light property
  
  if (lux > 300) {               // If the light level is greater than 300 (indicating sunlight)
    Serial.println("There is sunlight!!!");  //To print a message indicating sunlight
    Serial.print("Lux value: ");             //To print "Lux value: "
    Serial.println(intensity_light);         //To print the light intensity value
    delay(5000);                  // Adding delay for 5 seconds
  } else {                        // If the light level is not greater than 300 (no sunlight)
    Serial.println("No sunlight detected");  //To print a message indicating no sunlight
    Serial.print("Lux value: ");             //To print "Lux value: "
    Serial.println(intensity_light);         //To print the light intensity value
    delay(5000);                  // Adding delay for 5 seconds
  }
}
