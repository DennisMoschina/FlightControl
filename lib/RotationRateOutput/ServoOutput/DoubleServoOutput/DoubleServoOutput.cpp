#include "DoubleServoOutput.h"

DoubleServoOutput::DoubleServoOutput(SingleServoOutput* servoLeft, SingleServoOutput* servoRight, bool invertSecondServo = false) {
    this->servoLeft = servoLeft;
    this->servoRight = servoRight;
    this->secondServoInverter = invertSecondServo ? -1 : 1;
}

void DoubleServoOutput::write(int rate) {
    this->servoLeft->write(rate);
    this->servoRight->write(this->secondServoInverter * rate);
}

void DoubleServoOutput::setMiddle(int middle) {
    this->servoLeft->setMiddle(middle);
    this->servoRight->setMiddle(middle);
}

void DoubleServoOutput::setRange(int range) {
    this->servoLeft->setRange(range);
    this->servoRight->setRange(range);
}

void DoubleServoOutput::setLeftServoMiddle(int servoMiddle) {
    this->servoLeft->setMiddle(servoMiddle);
}

void DoubleServoOutput::setLeftServoRange(int range) {
    this->servoLeft->setRange(range);
}


void DoubleServoOutput::setRightServoMiddle(int servoMiddle) {
    this->servoRight->setMiddle(servoMiddle);
}

void DoubleServoOutput::setRightServoRange(int range) {
    this->servoRight->setRange(range);
}
