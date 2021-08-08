#ifndef _FILTERED_GYRO_H
#define _FILTERED_GYRO_H

#include <RotationReader.h>
#include <Filter.h>

class FilteredGyro : public Gyro {
public:
    FilteredGyro(Gyro* gyro, Filter<int, 3>* filter);

    RotationData getRotation();

private:
    Gyro* gyro;
    Filter<int, 3>* filter;
};

#endif