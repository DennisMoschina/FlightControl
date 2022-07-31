#include "SpeedBasedOutputCalculator.h"

SpeedBasedOutputCalculator::SpeedBasedOutputCalculator(AbstractOutputCalculator* outputCalculator,
                                                       SpeedReader *speedReader,
                                                       GainCalculator *gainCalculator) {
    this->outputCalculator = outputCalculator;
    this->speedReader = speedReader;
    this->gainCalculator = gainCalculator;
}

RotationData SpeedBasedOutputCalculator::calculateOutput(RotationData servoInput) {
    this->gainCalculator->calculateGains(this->speedReader->getSpeed());
    return this->outputCalculator->calculateOutput(servoInput);
}

int SpeedBasedOutputCalculator::getSteeringInputResolution() {
    return this->outputCalculator->getSteeringInputResolution();
}
int SpeedBasedOutputCalculator::getOutputResolution() {
    return this->outputCalculator->getOutputResolution();
}

void SpeedBasedOutputCalculator::reset() {
    this->outputCalculator->reset();
}