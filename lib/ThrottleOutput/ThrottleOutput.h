#ifndef _THROTTLE_OUTPUT_H
#define _THROTTLE_OUTPUT_H

/**
 * @brief An output for the throttle.
 * @author Dennis Moschina
 * @version 1.0
 */
class ThrottleOutput {
public:
    // /**
    //  * Write the amount of output to the throttle.
    //  * @param output the output for the throttle from 0 to ThrottleOutput#resolution
    //  */
    // virtual void write(int output) = 0;
    virtual void write(int rawData) = 0;

    // void setRange(int range) { this->range = range; }
    // void setResolution(int resolution) { this->resolution = resolution; }
    // int getResolution() { return this->resolution; }

protected:
    // int range;
    // int resolution;
};

#endif