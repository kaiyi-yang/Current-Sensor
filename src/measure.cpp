#include "header.h"
#include <Arduino.h>

Measure_Current::Measure_Current(uint8_t inPin, uint8_t vccPin, long zeroCurrentWaitTime, uint8_t correctionValue, 
                                    uint16_t iteration, float voltageReference, uint8_t bitResolution)
{
    _vin = inPin;
	_vccPin = vccPin;
	_bitResolution = bitResolution;
	_voltageReference = voltageReference;
	_zeroCurrentWaitTime =zeroCurrentWaitTime;
	_correctionValue = correctionValue;
	_iteration = iteration;

    pinMode(_vccPin, OUTPUT);
	digitalWrite(_vccPin, HIGH);
}


void Measure_Current::start()
{
    delay(_zeroCurrentWaitTime);	
	setZeroCurrent();				
}



void Measure_Current::setZeroCurrent()
{
    _zeroCurrentValue = getCurrent();
    _zeroCurrentSet = true;
		
    Serial.print("Zero Value Set to: ");
	Serial.println(_zeroCurrentValue);
	Serial.println("===========================");			   
}


float Measure_Current::getCurrent()
{
    float averageSensorValue = 0;
    int sensorValue;
    float voltage, current;

    for(int i=0; i<_iteration; i++)
    {
        sensorValue = analogRead(_vin);
        delay(2);

        voltage = (sensorValue) * (_voltageReference / (pow(2,_bitResolution)-1)) - (0.5 * _voltageReference) + _correctionValue; 
        current = voltage / 22.0;
 
        averageSensorValue += current;
    }    

    averageSensorValue /= _iteration;

    if(_zeroCurrentSet)
    {
        averageSensorValue -= _zeroCurrentValue;
    }

    return averageSensorValue;
}


void Measure_Current::printCurrent()
{
   Serial.println(getCurrent(), 2);
}
