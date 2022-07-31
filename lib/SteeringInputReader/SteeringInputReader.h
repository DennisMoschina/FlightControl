#ifndef _STEERING_INPUT_READER_H
#define _STEERING_INPUT_READER_H

#include <AxisData.h>

/**
 * @brief A reader for the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class SteeringInputReader {
public:
    /**
     * @brief Read the input from steering signals.
     * @return the percent of the steering signal
     */
    virtual RotationData readInput() = 0;

    /**
     * @brief Invert the inputs.
     * @param axis the axis to invert the input for (from 0 to 2)
     * @param invert the input should be inverted
     */
    void setInvert(int8_t axis, bool invert);
    /**
     * @brief Invert the inputs.
     * @param invert the input should be inverted
     */
    void setInvert(AxisData<bool> invert);

    /**
     * @brief Calibrate the input signals.
     * @todo implement
     */
    virtual void calibrate() = 0;

    /**
     * @brief Set the resolution for the input signals.
     * @param resolution the new resolution
     */
    void setResolution(int resolution);
    /**
     * @brief Get the resolution for the input signals.
     * @details The input signals can reach from -resolution to resolution
     */
    int getResolution();

protected:
    AxisData<bool> inverts;

    int resolution = 1024;
};

#endif