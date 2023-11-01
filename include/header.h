#ifndef HEADER
#define HEADER

#include <inttypes.h>


class Measure_Current{

public:

    Measure_Current(uint8_t inPin, uint8_t vccPin, long zeroCurrentWaitTime, uint8_t correctionValue, 
                    uint16_t iteration, float voltageReference, uint8_t bitResolution);

    void start();
    float getCurrent();
	void printCurrent();


private:

    void setZeroCurrent();
    int _vin, _vccPin;
    float _vcc, _current, _outVoltage, _zeroCurrentValue, _voltageReference;
    long _zeroCurrentWaitTime;
    uint8_t _correctionValue, _bitResolution;
    uint16_t _iteration;
    bool _zeroCurrentSet;

};

#endif