#ifndef _OUTPUT_CALCULATOR_H
#define _OUTPUT_CALCULATOR_H

#include <AxisData.h>
#include <Stabilizer.h>
#include <RotationReader.h>

/**
 * @brief Calculate the output based on the steering signal and the actual rotation.
 * @author Dennis Moschina
 * @version 1.0
 */
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

    /**
     * Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @param resolution the resolution of the servo inputs
     * @param throttleInput the signal for the throttle
     * @param throttleResolution the resolution of the throttle signal
     * @return the signal to output in percent to match the steering signal
     */
    RotationData calculateOutput(RotationData servoInput,
                                int resolution,
                                int throttleInput,
                                int throttleResolution);

    /**
     * Enable the stabilizer.
     * @param shouldCalculate the stabilizer is enabled
     */
    void setCalculate(boolean shouldCalculate);

private:
    Stabilizer* stabilizer;
    RotationReader* rotationReader;

    RotationData maxRates;

    boolean shouldCalculate = true;

    RotationData calculateSetpoint(RotationData input, int resolution);
};

#endif
