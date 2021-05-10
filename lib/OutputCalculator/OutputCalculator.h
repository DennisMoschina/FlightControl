#ifndef _OUTPUT_CALCULATOR_H
#define _OUTPUT_CALCULATOR_H

#include <AxisData.h>
#include <PID.h>
#include <RotationReader.h>

class OutputCalculator {
public:
    OutputCalculator(RotationData maxRates, RotationReader* rotationReader, PID* pid);

    RotationData calculateOutput(RotationData servoInput);

    void setCalculate(boolean shouldCalculate);
private:
    PID* pid;
    RotationReader* rotationReader;

    RotationData maxRates;

    boolean shouldCalculate = true;
};

#endif
