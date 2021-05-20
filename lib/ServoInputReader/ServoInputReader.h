#ifndef _SERVO_INPUT_READER_H
#define _SERVO_INPUT_READER_H

#include <ServoInput.h>
#include <AxisData.h>

class ServoInputReader {
public:
    ServoInputReader(AxisData<ServoInputSignal*> servoInputs);

    RotationData readInput();

    void calibrate();

private:
    AxisData<ServoInputSignal*> servoInputs;
};

#endif