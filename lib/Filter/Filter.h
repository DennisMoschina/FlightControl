#ifndef _FILTER_H
#define _FILTER_H

#include <stdexcept>
#include <array>

template<typename T, int dimensions = 1>
class Filter {
public:
    Filter() {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
    }

    virtual std::array<T, dimensions> addValue(T value[dimensions]) = 0;
};

#endif