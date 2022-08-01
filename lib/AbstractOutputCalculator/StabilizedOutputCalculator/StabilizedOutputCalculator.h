#ifndef _OUTPUT_CALCULATOR_H
#define _OUTPUT_CALCULATOR_H

#include <AxisData.h>
#include <Stabilizer.h>
#include <Gyro.h>
#include <GainCalculator.h>
#include <AbstractOutputCalculator.h>

/**
 * @brief Calculate the output based on the steering signal and the actual rotation.
 * @author Dennis Moschina
 * @version 1.0
 */
class StabilizedOutputCalculator: public AbstractOutputCalculator {
public:
    StabilizedOutputCalculator(int steeringInputResolution,
                        int outputResolution,
                        RotationData maxRates,
                        Gyro* rotationReader,
                        Stabilizer* stabilizer);

    /**
     * Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @return the signal to output in percent to match the steering signal
     */
    RotationData calculateOutput(RotationData servoInput);

    void reset();

private:
    Stabilizer* stabilizer;
    Gyro* rotationReader;

    RotationData maxRates;

    RotationData calculateSetpoint(RotationData input);
};

#endif
