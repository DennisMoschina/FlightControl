#include <RCReceiverReader.h>

template<unsigned char Pin>
RCReceiverReader<Pin>::RCReceiverReader(int16_t min, int16_t max) {
    this->setRange(min, max);
}

template<unsigned char Pin>
void RCReceiverReader<Pin>::setRange(int16_t min, int16_t max) {
    this->servo.setRange(min, max);
}

template<unsigned char Pin>
void RCReceiverReader<Pin>::setMin(int16_t min) {
    this->servo.setRangeMin(min);
}

template<unsigned char Pin>
void RCReceiverReader<Pin>::setMax(int16_t max) {
    this->servo.setRangeMax(max);
}


template<unsigned char Pin>
int16_t RCReceiverReader<Pin>::getPosition() {
    return this->servo.getPulseRaw();
}

template<unsigned char Pin>
float RCReceiverReader<Pin>::getAngle() {
    return 90 - this->servo.getAngle();
}
