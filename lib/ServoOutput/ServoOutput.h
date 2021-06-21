#ifndef _SERVO_OUTPUT_H
#define _SERVO_OUTPUT_H

#include <RotationRateOuput.h>

/**
 * @brief A {@link RotationRateOutput} in form of a servo.
 * @author Dennis Moschina
 * @version 1.0
 */
class ServoOutput: public RotationRateOutput {
public:
    /**
     * Trim the servo.
     * @param middle the new middle of the servo
     */
    virtual void setMiddle(int middle) = 0;
    /**
     * Set the new range of the servo.
     * @param range the new range for the servo
     */
    virtual void setRange(int range) = 0;
};

#endif