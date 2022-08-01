#include "ServoThrottleOutput.h"

ServoThrottleOutput::ServoThrottleOutput(Servo* output) {
    this->output = output;
}

void ServoThrottleOutput::write(int rawData) {
    log_v("about to write %d to output", rawData);
    this->output->writeMicroseconds(rawData);
}