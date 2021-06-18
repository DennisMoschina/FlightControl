#ifndef _ROTATION_RATE_OUTPUT_H
#define _ROTATION_RATE_OUTPUT_H

/**
 * @brief Write an amount of a maximal rotation rate to an output.
 * @author Dennis Moschina
 * @version 1.0
 */
class RotationRateOutput {
public:
    /**
     * @brief Write the rotation to an output.
     * @param rate the rate to write in percent
     */
    virtual void write(int rate) = 0;

    /**
     * @brief Set the resolution for the rate.
     * @param the new resolution
     */
    void setResolution(int resolution) {
        this->resolution = resolution;
    }

    /**
     * @brief Get the resolution for the rate.
     * @return the resolution for the rate
     */
    int getResoulution() {
        return this->resolution;
    }

protected:
    int resolution = 1024;
};

#endif