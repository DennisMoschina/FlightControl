#ifndef _FILTER_H
#define _FILTER_H

#include <stdexcept>

template<int dimensions = 1>
class Filter {
public:
    virtual float[dimensions] addValue(float[dimensions] value) = 0;
};

#endif