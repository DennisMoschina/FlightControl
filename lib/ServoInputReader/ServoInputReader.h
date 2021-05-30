#ifndef _SERVO_INPUT_READER_H
#define _SERVO_INPUT_READER_H

#include <ServoInput.h>
#include <AxisData.h>

class ServoInputReader {
public:
    ServoInputReader(AxisData<ServoInputSignal*> servoInputs);

    /**
     * Read the input from Servo signals.
     * @return the percent of the servo signal
     */
    RotationData readInput();

    void setInvert(byte axis, boolean invert);
    void setInvert(AxisData<boolean> invert);

    void calibrate();

    void setResolution(int resolution) {
        this->resolution = resolution;
    }

    int getResolution() {
        return this->resolution;
    }

private:
    AxisData<ServoInputSignal*> servoInputs;
    AxisData<boolean> inverts;

    int resolution = 1024;
};

#endif