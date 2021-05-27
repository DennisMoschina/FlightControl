#ifndef _SERVO_OUTPUT_H
#define _SERVO_OUTPUT_H

class ServoOutput {
public:
    virtual void setMiddle(int middle) = 0;
    virtual void setRange(int range) = 0;
};

#endif