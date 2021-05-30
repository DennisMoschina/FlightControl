#include <SingleServoOutput.h>

#define DEFAULT_SERVO_MIDDLE 1500
#define DEFAULT_SERVO_RANGE 1000

SingleServoOutput::SingleServoOutput(Servo* servo) {
    this->servo = servo;
    this->servoMiddle = DEFAULT_SERVO_MIDDLE;
    this->servoRange = DEFAULT_SERVO_RANGE;
}

void SingleServoOutput::write(int rate) {
    const int servoRadius = this->servoRange / 2;
    const int output = map(rate, -this->resolution, this->resolution,
                            this->servoMiddle - servoRadius,
                            this->servoMiddle + servoRadius);
    this->servo->writeMicroseconds(output);
}

void SingleServoOutput::setMiddle(int middle) {
    this->servoMiddle = middle;
}

void SingleServoOutput::setRange(int range) {
    this->servoRange = range;
}