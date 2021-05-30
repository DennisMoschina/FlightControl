#ifndef _STABILIZER_H
#define _STABILIZER_H

#include <AxisData.h>

class Stabilizer {
public:
    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @return the ratio of the maximum output (from -1024 to 1024)
     */
    virtual RotationData loop(RotationData setpoint, RotationData rotationRate) = 0;
    /**
     * Reset the stabilizer to its initial state. All settings are kept.
     */
    virtual void reset() = 0;
};

#endif
