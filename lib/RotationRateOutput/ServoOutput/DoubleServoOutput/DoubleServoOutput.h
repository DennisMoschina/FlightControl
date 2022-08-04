#ifndef _DOUBLE_SERVO_OUTPUT_H
#define _DOUBLE_SERVO_OUTPUT_H

#include <RotationRateOutput.h>
#include <ServoOutput/ServoOutput.h>
#include <ServoOutput/SingleServoOutput/SingleServoOutput.h>

class DoubleServoOutput: public ServoOutput {
public:
    DoubleServoOutput(SingleServoOutput* servoLeft, SingleServoOutput* servoRight, bool invertSecondServo = false);
    void write(int rate);

    void setMiddle(int servoMiddle);
    void setRange(int range);

    void setLeftServoMiddle(int servoMiddle);
    void setLeftServoRange(int range);

    void setRightServoMiddle(int servoMiddle);
    void setRightServoRange(int range);

private:
    SingleServoOutput* servoLeft;
    SingleServoOutput* servoRight;

    int8_t secondServoInverter;
};

#endif