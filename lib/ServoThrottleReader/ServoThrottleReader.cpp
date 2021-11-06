#include <ServoThrottleReader.h>

ServoThrottleReader::ServoThrottleReader(ServoInputSignal* input, int resolution, ThrottleOutput* throttleOutput): SpeedReader(resolution) {
    this->input = input;
    this->throttleOutput = throttleOutput;
}

int ServoThrottleReader::getSpeed() {
    if (this->throttleOutput != nullptr) {
        int rawSpeed = this->getRawSpeed();
        log_v("about to write %d to throttle output", rawSpeed);
        this->throttleOutput->write(rawSpeed);
        log_v("written to output successfully");
    }
    return this->input->map(0, resolution);
}

int ServoThrottleReader::getRawSpeed() {
    return this->input->getPulse();
}