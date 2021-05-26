#ifndef _AXIS_DATA_H
#define _AXIS_DATA_H

#define RAW_DATA_TYPE int16_t
#define ROTATION_DATA_TYPE int

#include <Arduino.h>
#include <stdexcept>


template<typename T> struct AxisData {
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
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
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

    inline AxisData<T>& operator=(const T& coords) {
        this->x = coords;
        this->y = coords;
        this->z = coords;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator+=(const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator+=(const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x += k;
        this->y += k;
        this->z += k;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator-=(const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator-=(const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x -= k;
        this->y -= k;
        this->z -= k;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator*=(const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }

    template<typename U>
    inline AxisData<T>& operator*=(const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        this->x *= k;
        this->y *= k;
        this->z *= k;
        return *this;
    }


    template<typename U>
    friend AxisData<T> operator+(AxisData<T> lhs, const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs += rhs;
    }
    template<typename U>
    friend AxisData<T> operator+(AxisData<T> lhs, const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs += k;
    }

    template<typename U>
    friend AxisData<T> operator-(AxisData<T> lhs, const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs -= rhs;
    }
    template<typename U>
    friend AxisData<T> operator-(AxisData<T> lhs, const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs -= k;
    }

    template<typename U>
    friend AxisData<T> operator*(AxisData<T> lhs, const AxisData<U>& rhs) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs *= rhs;
    }
    template<typename U>
    friend AxisData<T> operator*(AxisData<T> lhs, const U& k) {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");
        static_assert(std::is_arithmetic<U>::value, "U must be numeric");
        return lhs *= k;
    }
};

typedef AxisData<RAW_DATA_TYPE> RawAxisData;
typedef AxisData<ROTATION_DATA_TYPE> RotationData;

#endif
