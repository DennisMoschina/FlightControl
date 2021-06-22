#include <ServoThrottleOutput.h>

ServoThrottleOutput::ServoThrottleOutput(Servo* output) {
    this->output = output;
}

void ServoThrottleOutput::write(int rawData) {
    this->output->writeMicroseconds(rawData);
}