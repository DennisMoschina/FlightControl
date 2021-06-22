#ifndef _SERVO_THROTTLE_READER_H
#define _SERVO_THROTTLE_READER_H

#include <ThrottleReader.h>
#include <ServoInput.h>

class ServoThrottleReader: public ThrottleReader {
public:
    ServoThrottleReader(ServoInputSignal* input, int throttleResolution = 1024);

    int getThrottle();
    int getRawThrottle();

private:
    ServoInputSignal* input;
};

#endif