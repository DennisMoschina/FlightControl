#ifndef _AXIS_DATA_H
#define _AXIS_DATA_H

#define RAW_DATA_TYPE int16_t
#define ROTATION_DATA_TYPE float

#include <Arduino.h>
#include <stdexcept>


template<typename T> struct AxisData {
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");

    union {
        T x;
        T yaw;
    };
    union {
        T y;
        T pitch;
    };
    union {
        T z;
        T roll;
    };


    T& operator[](std::size_t idx) {
        assert(idx >= 0 && idx < 3);
        switch (idx) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
        }
        throw std::invalid_argument("Invalid axis!");
    }

    const T& operator[](std::size_t idx) const {
        assert(idx >= 0 && idx < 3);
        switch (idx) {
            case 0:
                return this->*x;
            case 1:
                return this->*y;
            case 2:
                return this->*z;
        }
        throw std::invalid_argument("Invalid axis!");
    }

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


    friend AxisData<T> operator+(AxisData<T> lhs, const AxisData<T>& rhs) {
        return lhs += rhs;
    }
    friend AxisData<T> operator+(AxisData<T> lhs, const T& k) {
        return lhs += k;
    }

    friend AxisData<T> operator-(AxisData<T> lhs, const AxisData<T>& rhs) {
        return lhs -= rhs;
    }
    friend AxisData<T> operator-(AxisData<T> lhs, const T& k) {
        return lhs -= k;
    }

    friend AxisData<T> operator*(AxisData<T> lhs, const AxisData<T>& rhs) {
        return lhs *= rhs;
    }
    friend AxisData<T> operator*(AxisData<T> lhs, const T& k) {
        return lhs *= k;
    }
};

typedef AxisData<RAW_DATA_TYPE> RawAxisData;
typedef AxisData<ROTATION_DATA_TYPE> RotationData;

#endif
