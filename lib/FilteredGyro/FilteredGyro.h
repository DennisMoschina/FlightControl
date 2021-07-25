#ifndef _FILTERED_GYRO_H
#define _FILTERED_GYRO_H

#include <RotationReader.h>
#include <Filter.h>

class FilteredGyro : public RotationReader {
public:
    FilteredGyro(RotationReader* gyro, Filter<int, 3>* filter);

    RotationData getRotation();

private:
    RotationReader* gyro;
    Filter<int, 3>* filter;
};

#endif