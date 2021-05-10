#ifndef _ROTATION_READER_H
#define _ROTATION_READER_H

#include <AxisData.h>

class RotationReader {
public:
    /**
     * Get the rotation rate in degrees per second.
     * @return rotation rate in deg/sec
     */
    virtual RotationData getRotation() = 0;
};

#endif
