#ifndef _IDLE_OUTPUT_CALCULATOR_H
#define _IDLE_OUTPUT_CALCULATOR_H

#include <AbstractOutputCalculator.h>
#include <AxisData.h>

/**
 * @brief This output calculator does not modify the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class IdleOutputCalculator: public AbstractOutputCalculator {
public:
    IdleOutputCalculator(int steeringInputResolution, int outputResolution);

    RotationData calculateOutput(RotationData servoInput);

    RotationData calculateOutput(RotationData servoInput,
                                int speed);
};

#endif