#ifndef _STABILIZER_H
#define _STABILIZER_H

#include <AxisData.h>

class Stabilizer {
public:
    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @return the ratio of the maximum output (from -#resolution to #resolution)
     */
    virtual RotationData loop(RotationData setpoint, RotationData rotationRate) = 0;

    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @param throttleSignal the signal for the throttle
     * @param throttleResolution the maximum value for the throttle
     * @return the ratio of the maximum output (from -#resolution to #resolution)
     */
    virtual RotationData loop(RotationData setpoint,
                                RotationData rotationRate,
                                int throttleSignal,
                                int throttleResolution) = 0;

    /**
     * Reset the stabilizer to its initial state. All settings are kept.
     */
    virtual void reset() = 0;

    void setResolution(int resolution) {
        this->resolution = resolution;
    }

    int getResolution() {
        return this->resolution;
    }

protected:
    int resolution = 1024;
};

#endif
