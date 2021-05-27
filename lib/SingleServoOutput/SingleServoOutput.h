#ifndef _SINGLE_SERVO_OUTPUT_H
#define _SINGLE_SERVO_OUTPUT_H

#include <RotationRateOuput.h>
#include <ESP32Servo.h>
#include <ServoOutput.h>

class SingleServoOutput: public RotationRateOutput, public ServoOutput {
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