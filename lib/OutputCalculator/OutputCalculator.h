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
class OutputCalculator: public AbstractOutputCalculator {
public:
    OutputCalculator(int steeringInputResolution,
                        int outputResolution,
                        RotationData maxRates,
                        Gyro* rotationReader,
                        Stabilizer* stabilizer,
                        GainCalculator* gainCalculator = nullptr);

    /**
     * Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @return the signal to output in percent to match the steering signal
     */
    RotationData calculateOutput(RotationData servoInput);

    /**
     * Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @param speed the signal for the throttle
     * @return the signal to output in percent to match the steering signal
     */
    RotationData calculateOutput(RotationData servoInput,
                                int speed);

    void reset();

private:
    Stabilizer* stabilizer;
    Gyro* rotationReader;
    GainCalculator* gainCalculator;

    RotationData maxRates;

    RotationData calculateSetpoint(RotationData input);
};

#endif
