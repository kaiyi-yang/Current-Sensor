#include <Arduino.h>
#include <header.h>

#define SENSOR_PIN 25 //pin for reading sensor
#define SENSOR_VCC_PIN 21 //pin for powring up the sensor

#define ZERO_CURRENT_WAIT_TIME 2000 //wait for 5 seconds to allow zero current measurement
#define CORRECTION_VLALUE 164 //mA
#define MEASUREMENT_ITERATION 20
#define VOLTAGE_REFERENCE  5000.0 //5000mv is for 5V
#define BIT_RESOLUTION 10

Measure_Current sensor(SENSOR_PIN, SENSOR_VCC_PIN, ZERO_CURRENT_WAIT_TIME, CORRECTION_VLALUE, 
                        MEASUREMENT_ITERATION, VOLTAGE_REFERENCE, BIT_RESOLUTION);

float a = analogRead(SENSOR_PIN);

void setup()
{ 
  Serial.begin(9600);
  Serial.println("Welcome");
  Serial.println("======================");
  sensor.start();
}

void loop()
{
  while(Serial.available())
  {
    if('1' == Serial.read())
    {
      int d=0;
        while(d<1)
        {
        sensor.printCurrent();
        if ('2'==Serial.read()){d=2;break;} 
        }
    }    
  }
}
