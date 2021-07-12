#ifndef _EWMA_H
#define _EWMA_H

#include <Filter.h>
#include <limits>
#include <cmath>

class EWMA : public Filter {
public:
    EWMA(float alpha = 0.2);

    float addValue(float value);

private:
    float alpha;

    float value = std::numeric_limits<float>::quiet_NaN();
};

#endif