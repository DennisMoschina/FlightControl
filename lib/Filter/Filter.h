#ifndef _FILTER_H
#define _FILTER_H

#include <stdexcept>

class Filter {
public:
    virtual float addValue(float value) = 0;
};

#endif