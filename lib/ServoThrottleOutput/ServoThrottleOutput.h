#ifndef _SERVO_THROTTLE_OUTPUT_H
#define _SERVO_THROTTLE_OUTPUT_H

#include <ThrottleOutput.h>
#include <ESP32Servo.h>

class ServoThrottleOutput: public ThrottleOutput {
public:
    ServoThrottleOutput(Servo* output);
    void write(int rawData);
    
private:
    Servo* output;
};

#endif