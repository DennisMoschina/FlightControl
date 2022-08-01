#include "ServoThrottleReader.h"

ServoThrottleReader::ServoThrottleReader(ServoInputSignal* input, int resolution, ThrottleOutput* throttleOutput): ThrottleReader(resolution, throttleOutput) {
    this->input = input;
}

int ServoThrottleReader::getRawSpeed() {
    return this->input->getPulse();
}