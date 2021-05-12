#ifndef _OUTPUT_CALCULATOR_H
#define _OUTPUT_CALCULATOR_H

#include <AxisData.h>
#include <Stabilizer.h>
#include <RotationReader.h>

class OutputCalculator {
public:
    OutputCalculator(RotationData maxRates, RotationReader* rotationReader, Stabilizer* stabilizer);

    RotationData calculateOutput(RotationData servoInput);

    void setCalculate(boolean shouldCalculate);

    void setServoMiddle(AxisData<int> servoMiddle);
    void setServoMiddle(byte axis, int servoMiddle);

private:
    Stabilizer* stabilizer;
    RotationReader* rotationReader;

    RotationData maxRates;

    boolean shouldCalculate = true;

    AxisData<int> servoMiddle;
    AxisData<int> servoRange;

    RotationData remapOutput(RotationData output);
};

#endif
