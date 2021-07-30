#ifndef _OVERFLOW_FILTER_H
#define _OVERFLOW_FILTER_H

#include <Filter.h>

template <typename T, int dimensions = 1>
class OverflowFilter: public Filter<T, dimensions> {
public:
    std::array<T, dimensions> addValue(T value[dimensions]);

private:
    int delta[dimensions];
    T oldValue[dimensions];

    bool isOverflown(T value, int i);
};

template<typename T, int dimensions>
std::array<T, dimensions> OverflowFilter<T, dimensions>::addValue(T value[dimensions]) {
    std::array<T, dimensions> output;
    for (int i = 0; i < dimensions; i++) {
        output[i] = (this->isOverflown(value[i], i) ? -1 : 1) * value[i];
        this->delta[i] = output[i] - this->oldValue[i];
        this->oldValue[i] = output[i];
    }

    return output;
}

template<typename T, int dimensions>
bool OverflowFilter<T, dimensions>::isOverflown(T value, int i) {
    if (abs(this->delta[i]) < 1 || (this->oldValue[i] < 0 == value < 0)) return false;
    int expectedValue = this->oldValue[i] + this->delta[i];
    return abs(expectedValue - value) > abs(expectedValue + value);
}

#endif