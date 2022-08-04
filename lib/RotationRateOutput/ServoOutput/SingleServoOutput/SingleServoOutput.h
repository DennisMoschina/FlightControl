#ifndef _SINGLE_SERVO_OUTPUT_H
#define _SINGLE_SERVO_OUTPUT_H

#include <RotationRateOutput.h>
#include <ESP32Servo.h>
#include <ServoOutput/ServoOutput.h>

class SingleServoOutput: public ServoOutput {
public:
    SingleServoOutput(Servo* servo);
    void write(int rate);

    void setMiddle(int servoMiddle);
    void setRange(int range);

private:
    Servo* servo;
    int servoMiddle;
    int servoRange;
};

#endif