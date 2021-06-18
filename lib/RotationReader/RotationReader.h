#ifndef _ROTATION_READER_H
#define _ROTATION_READER_H

#include <AxisData.h>

/**
 * @brief Read the rotation rate.
 * @author Dennis Moschina
 * @version 1.0
 */
class RotationReader {
public:
    /**
     * Get the rotation rate in degrees per second.
     * @return rotation rate in deg/sec
     */
    virtual RotationData getRotation() = 0;
};

#endif
