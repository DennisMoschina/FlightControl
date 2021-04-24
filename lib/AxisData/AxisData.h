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

    struct AxisData<T>& operator=(const T coords[3]) {
        this->x = coords[0];
        this->y = coords[1];
        this->z = coords[2];
        return *this;
    }

    struct AxisData<T>& operator=(const T& coords) {
        this->x = coords;
        this->y = coords;
        this->z = coords;
        return *this;
    }

    struct AxisData<T>& operator+=(const AxisData<T>& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    struct AxisData<T>& operator+=(const T& k) {
        this->x += k;
        this->y += k;
        this->z += k;
        return *this;
    }

    struct AxisData<T>& operator-=(const AxisData<T>& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    struct AxisData<T>& operator-=(const T& k) {
        this->x -= k;
        this->y -= k;
        this->z -= k;
        return *this;
    }

    struct AxisData<T>& operator*=(const AxisData<T>& rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }

    struct AxisData<T>& operator*=(const T& k) {
        this->x *= k;
        this->y *= k;
        this->z *= k;
        return *this;
    }
};

template<typename T>
AxisData<T> operator+(AxisData<T> lhs, const AxisData<T>& rhs);
template<typename T>
AxisData<T> operator+(AxisData<T> lhs, T& k);

template<typename T>
AxisData<T> operator-(AxisData<T> lhs, const AxisData<T>& rhs);
template<typename T>
AxisData<T> operator-(AxisData<T> lhs, T& k);

template<typename T>
AxisData<T> operator*(AxisData<T> lhs, const AxisData<T>& rhs);
template<typename T>
AxisData<T> operator*(AxisData<T> lhs, T& k);

typedef AxisData<RAW_DATA_TYPE> RawAxisData;
typedef AxisData<ROTATION_DATA_TYPE> RotationData;

#endif
