#ifndef _SERVO_INPUT_READER_H
#define _SERVO_INPUT_READER_H

#include <ServoInput.h>
#include <AxisData.h>

/**
 * @brief A reader for the servo signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class ServoInputReader {
public:
    ServoInputReader(AxisData<ServoInputSignal*> servoInputs);

    /**
     * @brief Read the input from Servo signals.
     * @return the percent of the servo signal
     */
    RotationData readInput();

    /**
     * @brief Invert the inputs.
     * @param axis the axis to invert the input for (from 0 to 2)
     * @param invert the input should be inverted
     */
    void setInvert(byte axis, boolean invert);
    /**
     * @brief Invert the inputs.
     * @param invert the input should be inverted
     */
    void setInvert(AxisData<boolean> invert);

    /**
     * @brief Calibrate the input signals.
     * @todo implement
     */
    void calibrate();

    /**
     * @brief Set the resolution for the input signals.
     * @param resolution the new resolution
     */
    void setResolution(int resolution) {
        this->resolution = resolution;
    }

    /**
     * @brief Get the resolution for the input signals.
     * @details The input signals can reach from -resolution to resolution
     */
    int getResolution() {
        return this->resolution;
    }

private:
    AxisData<ServoInputSignal*> servoInputs;
    AxisData<boolean> inverts;

    int resolution = 1024;
};

#endif