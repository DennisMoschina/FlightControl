#ifndef _RC_RECEIVER_READER_H
#define _RC_RECEIVER_READER_H

#include <Arduino.h>
#include <ServoInput.h>

template<uint8_t Pin>
class RCReceiverReader {
public:
    RCReceiverReader();
    RCReceiverReader(int16_t min, int16_t max);
    void begin();

    int16_t getPosition();
    float getAngle();

    void setRange(int16_t min, int16_t max);
    void setMin(int16_t min);
    void setMax(int16_t max);

private:
    int16_t min;
    int16_t max;

    ServoInputPin<Pin> servo;
};

#endif
