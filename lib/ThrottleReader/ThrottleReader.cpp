#include "ThrottleReader.h"

ThrottleReader::ThrottleReader(int throttleResolution, ThrottleOutput* throttleOutput): SpeedReader(throttleResolution) {
    this->throttleOutput = throttleOutput;
}

int ThrottleReader::getSpeed() {
    if (this->throttleOutput != nullptr) {
        int rawSpeed = this->getRawSpeed();
        log_v("about to write %d to throttle output", rawSpeed);
        this->throttleOutput->write(rawSpeed);
        log_v("written to output successfully");
        return rawSpeed;
    }
    return -1;
}