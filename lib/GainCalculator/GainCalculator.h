#ifndef _GAIN_CALCULATOR_H
#define _GAIN_CALCULATOR_H

#include <AxisData.h>

typedef AxisData<float> CorrectionData;

class GainCalculator {
public:
    virtual void calculateGains(int speed) = 0;

    void setSpeedResolution(int resolution) {
        this->speedResolution = resolution;
    }

protected:
    int speedResolution;
};

#endif