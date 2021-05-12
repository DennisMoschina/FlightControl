#ifndef _STABILIZER_H
#define _STABILIZER_H

#include <AxisData.h>

class Stabilizer {
public:
    virtual RotationData loop(RotationData setpoint, RotationData rotationRate);
};

#endif
