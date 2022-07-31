#ifndef _ABSTRACT_OUTPUT_CALCULATOR_H
#define _ABSTRACT_OUTPUT_CALCULATOR_H

#include <AxisData.h>

/**
 * @brief Calculate the output based on the steering signal and the actual rotation.
 * @author Dennis Moschina
 * @version 1.0
 */
class AbstractOutputCalculator {
public:
    AbstractOutputCalculator(int steeringInputResolution, int outputResolution, int speedResolution = 0):
        steeringInputResolution(steeringInputResolution),
        outputResolution(outputResolution) {}

    /**
     * @brief Calculate the output to match the steering signals.
     * @param servoInput the steering signal in percent of the maximum rates
     * @return the signal to output in percent to match the steering signal
     */
    virtual RotationData calculateOutput(RotationData servoInput) = 0;

    /**
     * @brief Reset any settings or other stuff inside the outputcalculator which might
     * change by using it.
     */
    virtual void reset() {}

    int getSteeringInputResolution() {
        return this->steeringInputResolution;
    }
    int getOutputResolution() {
        return this->outputResolution;
    }

protected:
    AbstractOutputCalculator(): steeringInputResolution(-1), outputResolution(-1) {}

    RotationData adjustOutput(RotationData output, int fromResolution) {
        RotationData adjustedOutput;
        for (int i = 0; i < 3; i++)
        adjustedOutput[i] = map(output[i], -fromResolution, fromResolution, -this->outputResolution, this->outputResolution);

        return adjustedOutput;
    }

private:
    const int steeringInputResolution;
    const int outputResolution;
};

#endif
