#include <ServoThrottleReader.h>

ServoThrottleReader::ServoThrottleReader(ServoInputSignal* input, int resolution): SpeedReader(resolution) {
    this->input = input;
}

int ServoThrottleReader::getSpeed() {
    return this->input->map(0, resolution);
}

int ServoThrottleReader::getRawSpeed() {
    return this->input->getPulse();
}