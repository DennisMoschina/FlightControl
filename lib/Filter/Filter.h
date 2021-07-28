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

template<typename T, int dimensions = 1>
class CombinedFilter : public Filter<T, dimensions> {
public:
    CombinedFilter(Filter<T, dimensions>* firstFilter, Filter<T, dimensions>* secondFilter) {
        this->firstFilter = firstFilter;
        this->secondFilter = secondFilter;
    }

    std::array<T, dimensions> addValue(T value[dimensions]) {
        std::array<T, dimensions> filteredValue = this->firstFilter->addValue(value);
        T filteredArr[dimensions];
        for (int i = 0; i < dimensions; i++) filteredArr[i] = filteredValue[i];
        return this->secondFilter->addValue(filteredArr);
    }

private:
    Filter<T, dimensions>* firstFilter;
    Filter<T, dimensions>* secondFilter;
};

#endif