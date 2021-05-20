#ifndef _SERVO_INPUT_READER_H
#define _SERVO_INPUT_READER_H

#include <ServoInput.h>

class ServoInputReader {
public:
    ServoInputReader(AxisData<ServoInputSignal*> servoInputs) {
        this->servoInputs = servoInputs;
    }

    AxisData<int16_t> readInput() {
        AxisData<int16_t> inputs;
        inputs.x = this->servoInputs.x->map(-100, 100);
        inputs.y = this->servoInputs.y->map(-100, 100);
        inputs.z = this->servoInputs.z->map(-100, 100);
        return inputs;
    }

private:
    AxisData<ServoInputSignal*> servoInputs;
};

#endif