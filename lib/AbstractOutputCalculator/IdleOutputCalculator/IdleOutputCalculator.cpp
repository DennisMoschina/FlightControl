#include "IdleOutputCalculator.h"

IdleOutputCalculator::IdleOutputCalculator(int steeringInputResolution, int outputResolution):
    AbstractOutputCalculator(steeringInputResolution, outputResolution) {}


RotationData IdleOutputCalculator::calculateOutput(RotationData servoInput) {
    return this->adjustOutput(servoInput, this->getSteeringInputResolution());
}

RotationData IdleOutputCalculator::calculateOutput(RotationData servoInput, int speed) {
    return this->calculateOutput(servoInput);
}