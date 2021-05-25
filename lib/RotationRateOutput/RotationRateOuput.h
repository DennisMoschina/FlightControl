#ifndef _ROTATION_RATE_OUTPUT_H
#define _ROTATION_RATE_OUTPUT_H

class RotationRateOutput {
public:
    /**
     * Write the rotation to an output.
     * @param rate the rate to write in percent
     */
    virtual void write(int rate) = 0;
};

#endif