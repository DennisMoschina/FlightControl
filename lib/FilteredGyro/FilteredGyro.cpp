#include <FilteredGyro.h>

FilteredGyro::FilteredGyro(RotationReader* gyro, Filter<int, 3>* filter) {
    this->gyro = gyro;
    this->filter = filter;
}

RotationData FilteredGyro::getRotation() {
    RotationData gyroData = this->gyro->getRotation();
    int gyroArr[3] = {gyroData[0], gyroData[1], gyroData[2]};
    std::array<int, 3> filteredData = this->filter->addValue(gyroArr);
    return {filteredData[0], filteredData[1], filteredData[2]};
}