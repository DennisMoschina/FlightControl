#include "SteeringInputReader.h"

void SteeringInputReader::setInvert(int8_t axis, bool invert) {
    this->inverts[axis] = invert;
}

void SteeringInputReader::setInvert(AxisData<bool> invert) {
    this->inverts = invert;
}

void SteeringInputReader::setResolution(int resolution) {
    this->resolution = resolution;
}

int SteeringInputReader::getResolution() {
    return this->resolution;
}