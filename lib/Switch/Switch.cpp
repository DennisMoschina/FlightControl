#include <Switch.h>

Switch::Switch(int positions): positions(positions) { }

int Switch::getNumberOfPositions() {
    return this->positions;
}