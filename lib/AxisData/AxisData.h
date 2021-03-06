#ifndef _AXIS_DATA_H
#define _AXIS_DATA_H

#define RAW_DATA_TYPE int16_t
#define ROTATION_DATA_TYPE int

#include <Arduino.h>
#include <stdexcept>

/**
 * @brief An ordered triple of some type.
 * @author Dennis Moschina
 * @version 1.0
 */
template<typename T> struct AxisData {
    static const int YAW = 0;
    static const int X = 0;
    static const int PITCH = 1;
    static const int Y = 1;
    static const int ROLL = 2;
    static const int Z = 2;

    union {
        T x;
        T yaw;
        T rudder;
    };
    union {
        T y;
        T pitch;
        T elevator;
    };
    union {
        T z;
        T roll;
        T aileron;
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
