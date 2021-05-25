#ifndef _SINGLE_SERVO_OUTPUT_H
#define _SINGLE_SERVO_OUTPUT_H

#include <RotationRateOuput.h>
#include <ESP32Servo.h>

class SingleServoOutput: public RotationRateOutput {
public:
    SingleServoOutput(Servo* servo);
    void write(int rate);

    void setMiddle(int middle) {
        this->servoMiddle = middle;
    }
    void setRange(int range) {
        this->servoRange = range;
    }

private:
    Servo* servo;

    int servoMiddle;
    int servoRange;
};

#endif