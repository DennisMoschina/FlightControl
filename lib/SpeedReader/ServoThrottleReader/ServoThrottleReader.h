#ifndef _SERVO_THROTTLE_READER_H
#define _SERVO_THROTTLE_READER_H

#include <ThrottleReader/ThrottleReader.h>
#include <ServoInput.h>
#include <ThrottleOutput.h>

class ServoThrottleReader: public ThrottleReader {
public:
    ServoThrottleReader(ServoInputSignal* input, int throttleResolution = 1024, ThrottleOutput* throttleOutput = nullptr);
private:
    ServoInputSignal* input;

    int getRawSpeed();
};

#endif