#include <ServoThrottleReader.h>

ServoThrottleReader::ServoThrottleReader(ServoInputSignal* input, int resolution): ThrottleReader(resolution) {
    this->input = input;
}

int ServoThrottleReader::getThrottle() {
    return this->input->map(0, resolution);
}

int ServoThrottleReader::getRawThrottle() {
    return this->input->getPulse();
}