#include <ServoThrottleReader.h>

ServoThrottleReader::ServoThrottleReader(ServoInputSignal* input, int resolution, ThrottleOutput* throttleOutput): SpeedReader(resolution) {
    this->input = input;
}

int ServoThrottleReader::getSpeed() {
    if (this->throttleOutput != nullptr) this->throttleOutput->write(this->getRawSpeed());
    return this->input->map(0, resolution);
}

int ServoThrottleReader::getRawSpeed() {
    return this->input->getPulse();
}