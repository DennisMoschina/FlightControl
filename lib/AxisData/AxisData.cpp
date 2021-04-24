#include <AxisData.h>

/*
template<typename T>
AxisData<T> AxisData<T>::operator+(AxisData<T> summand) {
    AxisData<T> result;
    result.x = this.x + summand.x;
    result.y = this.y + summand.y;
    result.z = this.z + summand.z;
    return result;
}

template<typename T>
AxisData<T> AxisData<T>::operator-(AxisData<T> subtrahend) {
    AxisData<T> result;
    result.x = this.x - subtrahend.x;
    result.y = this.y - subtrahend.y;
    result.z = this.z - subtrahend.z;
    return result;
}

template<typename T>
AxisData<T> AxisData<T>::operator*(int factor) {
    AxisData<T> result;
    result.x = this.x * factor;
    result.y = this.y * factor;
    result.z = this.z * factor;
    return result;
}

// template<typename T>
// AxisData<T> AxisData<T>::operator*(float factor) {
//     AxisData<T> result;
//     result.x = this.x * factor;
//     result.y = this.y * factor;
//     result.z = this.z * factor;
//     return result;
// }

template<typename T>
AxisData<T> AxisData<T>::operator/(int divident) {
    AxisData<T> result;
    result.x = this.x / divident;
    result.y = this.y / divident;
    result.z = this.z / divident;
    return result;
}

// template<typename T>
// AxisData<T> AxisData<T>::operator/(float divident) {
//     AxisData<T> result;
//     result.x = this.x / divident;
//     result.y = this.y / divident;
//     result.z = this.z / divident;
//     return result;
// }


template<typename T>
void AxisData<T>::operator+=(AxisData<T> summand) {
    this.x = this.x + summand.x;
    this.y = this.y + summand.y;
    this.z = this.z + summand.z;
}

template<typename T>
void AxisData<T>::operator-=(AxisData<T> subtrahend) {
    this.x = this.x - subtrahend.x;
    this.y = this.y - subtrahend.y;
    this.z = this.z - subtrahend.z;
}
*/






template<typename R, typename U, typename S>
AxisData<R> operator+(AxisData<U> s1, S s2) {
    static_assert(std::is_arithmetic<S>::value, "S must be numeric");

    AxisData<R> result;
    result.x = s1.x + s2;
    result.y = s1.y + s2;
    result.z = s1.z + s2;
    return result;
}

template<typename R, typename U, typename S>
AxisData<R> operator+(U s1, AxisData<S> s2) {
    return operator+(s2, s1);
}

template<typename R, typename U, typename S>
AxisData<R> operator+(AxisData<U> s1, AxisData<S> s2) {
    AxisData<R> result;
    result.x = s1.x + s2.x;
    result.y = s1.y + s2.y;
    result.z = s1.z + s2.z;
    return result;
}


template<typename R, typename U, typename S>
AxisData<R> operator-(AxisData<U> minuend, S subtrahend) {
    static_assert(std::is_arithmetic<S>::value, "S must be numeric");

    AxisData<R> result;
    result.x = minuend.x - subtrahend;
    result.y = minuend.y - subtrahend;
    result.z = minuend.z - subtrahend;
    return result;
}

template<typename R, typename U, typename S>
AxisData<R> operator-(U minuend, AxisData<S> subtrahend) {
    return -1 * (subtrahend - minuend);
}

template<typename R, typename U, typename S>
AxisData<R> operator-(AxisData<U> minuend, AxisData<S> subtrahend) {
    AxisData<R> result;
    result.x = minuend.x - subtrahend.x;
    result.y = minuend.y - subtrahend.y;
    result.z = minuend.z - subtrahend.z;
    return result;
}


template<typename R, typename U, typename S>
AxisData<R> operator*(AxisData<U> f1, S f2) {
    static_assert(std::is_arithmetic<S>::value, "S must be numeric");

    AxisData<R> result;
    result.x = f1.x * f2;
    result.y = f1.y * f2;
    result.z = f1.z * f2;
    return result;
}

template<typename R, typename U, typename S>
AxisData<R> operator*(U f1, AxisData<S> f2) {
    return operator*(f2, f1);
}

template<typename R, typename U, typename S>
AxisData<R> operator*(AxisData<U> f1, AxisData<S> f2) {
    AxisData<R> result;
    result.x = f1.x * f2.x;
    result.y = f1.y * f2.y;
    result.z = f1.z * f2.z;
    return result;
}


template<typename U, typename S>
AxisData<U>& operator+=(AxisData<U> s1, S s2) {
    s1 = s1 + s2;
    return *s1;
}

template<typename U, typename S>
AxisData<U>& operator+=(AxisData<U> s1, AxisData<S> s2) {
    s1 = s1 + s2;
    return *s1;
}


template<typename U, typename S>
AxisData<U>& operator-=(AxisData<U> minuend, S subtrahend) {
    minuend = minuend - subtrahend;
    return *minuend;
}
template<typename U, typename S>
AxisData<U>& operator-=(AxisData<U> minuend, AxisData<S> subtrahend) {
    minuend = minuend - subtrahend;
    return *minuend;
}
