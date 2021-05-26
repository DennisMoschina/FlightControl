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

    void calibrate();

private:
    AxisData<ServoInputSignal*> servoInputs;
};

#endif