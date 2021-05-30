#include <ServoInputReader.h>

ServoInputReader::ServoInputReader(AxisData<ServoInputSignal*> servoInputs) {
    this->servoInputs = servoInputs;
    this->inverts = false;
}

RotationData ServoInputReader::readInput() {
    RotationData inputs;
    inputs.x = this->servoInputs.x->map(-this->resolution, this->resolution);
    inputs.y = this->servoInputs.y->map(-this->resolution, this->resolution);
    inputs.z = this->servoInputs.z->map(-this->resolution, this->resolution);

    for (int i = 0; i < 3; i++) {
        if (this->inverts[i]) {
            inputs[i] = -inputs[i];
        }
    }
    return inputs;
}

void ServoInputReader::setInvert(byte axis, boolean invert) {
    this->inverts[axis] = invert;
}

void ServoInputReader::setInvert(AxisData<boolean> invert) {
    this->inverts = invert;
}

void ServoInputReader::calibrate() {}