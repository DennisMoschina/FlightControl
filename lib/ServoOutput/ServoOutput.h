#ifndef _SERVO_OUTPUT_H
#define _SERVO_OUTPUT_H

#include <RotationRateOuput.h>

class ServoOutput: public RotationRateOutput {
public:
    virtual void setMiddle(int middle) = 0;
    virtual void setRange(int range) = 0;
};

#endif