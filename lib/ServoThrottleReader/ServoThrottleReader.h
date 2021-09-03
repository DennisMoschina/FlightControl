#ifndef _SERVO_THROTTLE_READER_H
#define _SERVO_THROTTLE_READER_H

#include <SpeedReader.h>
#include <ServoInput.h>
#include <ThrottleOutput.h>

class ServoThrottleReader: public SpeedReader {
public:
    ServoThrottleReader(ServoInputSignal* input, int throttleResolution = 1024, ThrottleOutput* throttleOutput = nullptr);

    int getSpeed();
    int getRawSpeed();

private:
    ServoInputSignal* input;
    ThrottleOutput* throttleOutput;
};

#endif