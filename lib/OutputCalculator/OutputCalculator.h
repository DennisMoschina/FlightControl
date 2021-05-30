#ifndef _OUTPUT_CALCULATOR_H
#define _OUTPUT_CALCULATOR_H

#include <AxisData.h>
#include <Stabilizer.h>
#include <RotationReader.h>

class OutputCalculator {
public:
    OutputCalculator(RotationData maxRates, RotationReader* rotationReader, Stabilizer* stabilizer);

    /**
     * Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @param resolution the resolution of the servo inputs
     * @return the signal to output in percent to match the steering signal
     */
    RotationData calculateOutput(RotationData servoInput, int resolution);

    void setCalculate(boolean shouldCalculate);

private:
    Stabilizer* stabilizer;
    RotationReader* rotationReader;

    RotationData maxRates;

    boolean shouldCalculate = true;
};

#endif
