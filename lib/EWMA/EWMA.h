#ifndef _EWMA_H
#define _EWMA_H

#include <Filter.h>

template<typename T, int dimensions = 1>
class EWMA : public Filter<T, dimensions> {
public:
    EWMA(float alpha[dimensions]);
    EWMA(float alpha = 0.2);

    std::array<T, dimensions> addValue(T value[dimensions]);

private:
    float alpha[dimensions];

    T value[dimensions];

    bool hasValue = false;
};




template<typename T, int dimensions>
EWMA<T, dimensions>::EWMA(float alpha[dimensions]) {
    this->alpha = alpha;
}

template<typename T, int dimensions>
EWMA<T, dimensions>::EWMA(float alpha) {
    for (int i = 0; i < dimensions; i++) {
        this->alpha[i] = alpha;
    }
}


template<typename T, int dimensions>
std::array<T, dimensions> EWMA<T, dimensions>::addValue(T value[]) {
    if (this->hasValue) {
        for (int i = 0; i < dimensions; i++) {
            this->value[i] = (1 - this->alpha[i]) * this->value[i] + this->alpha[i] * value[i];
        }
    } else {
        for (int i = 0; i < dimensions; i++) this->value[i] = value[i];
        this->hasValue = true;
    }

    std::array<T, dimensions> output;
    for (int i = 0; i < dimensions; i++) output[i] = this->value[i];
    return output;
}

#endif