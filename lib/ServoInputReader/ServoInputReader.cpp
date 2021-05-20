#include <ServoInputReader.h>

ServoInputReader::ServoInputReader(AxisData<ServoInputSignal*> servoInputs) {
    this->servoInputs = servoInputs;
}

RotationData ServoInputReader::readInput() {
    RotationData inputs;
    inputs.x = this->servoInputs.x->map(-100, 100);
    inputs.y = this->servoInputs.y->map(-100, 100);
    inputs.z = this->servoInputs.z->map(-100, 100);
    return inputs;
}

void ServoInputReader::calibrate() {}