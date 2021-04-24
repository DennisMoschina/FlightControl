#ifndef _AXIS_DATA_H
#define _AXIS_DATA_H

#define RAW_DATA_TYPE int16_t
#define ROTATION_DATA_TYPE float

#include <Arduino.h>

#include <type_traits>

template<typename T> struct AxisData {
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");
    T x;
    T y;
    T z;

    // template<typename R, typename U, typename S>
    // friend AxisData<R> operator/(U divident);
    //
    // template<typename R, typename U, typename S>
    // friend void operator+=(AxisData<U> summand);
    // template<typename R, typename U, typename S>
    // friend void operator-=(AxisData<U> subtrahend);
};

template<typename R, typename U, typename S>
AxisData<R> operator+(AxisData<U> s1, S s2);
template<typename R, typename U, typename S>
AxisData<R> operator+(U s1, AxisData<S> s2);
template<typename R, typename U, typename S>
AxisData<R> operator+(AxisData<U> s1, AxisData<S> s2);

template<typename R, typename U, typename S>
AxisData<R> operator-(AxisData<U> minuend, S subtrahend);
template<typename R, typename U, typename S>
AxisData<R> operator-(U minuend, AxisData<S> subtrahend);
template<typename R, typename U, typename S>
AxisData<R> operator-(AxisData<U> minuend, AxisData<S> subtrahend);

template<typename R, typename U, typename S>
AxisData<R> operator*(AxisData<U> f1, S f2);
template<typename R, typename U, typename S>
AxisData<R> operator*(U f1, AxisData<S> f2);
template<typename R, typename U, typename S>
AxisData<R> operator*(AxisData<U> f1, AxisData<S> f2);

template<typename U, typename S>
AxisData<U>& operator+=(AxisData<U> s1, S s2);
template<typename U, typename S>
AxisData<U>& operator+=(AxisData<U> s1, AxisData<S> s2);

template<typename U, typename S>
AxisData<U>& operator-=(AxisData<U> minuend, S subtrahend);
template<typename U, typename S>
AxisData<U>& operator-=(AxisData<U> minuend, AxisData<S> subtrahend);

typedef AxisData<RAW_DATA_TYPE> RawAxisData;
typedef AxisData<ROTATION_DATA_TYPE> RotationData;

#endif
