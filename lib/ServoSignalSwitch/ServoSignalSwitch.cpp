#include <ServoSignalSwitch.h>

ServoSignalSwitch::ServoSignalSwitch(int positions, ServoInputSignal* servoInput): Switch(positions) {
    this->servoInput = servoInput;
}

int ServoSignalSwitch::getPosition() {
    return this->servoInput->map(0, this->getNumberOfPositions() - 1);
}