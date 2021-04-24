#include <AxisData.h>

template<typename T>
AxisData<T> operator+(AxisData<T> lhs, const AxisData<T>& rhs){
    return lhs += rhs;
}
template<typename T>
AxisData<T> operator+(AxisData<T> lhs, T& k) {
    return lhs += k;
}

template<typename T>
AxisData<T> operator-(AxisData<T> lhs, const AxisData<T>& rhs) {
    return lhs -= rhs;
}
template<typename T>
AxisData<T> operator-(AxisData<T> lhs, T& k) {
    return lhs -= k;
}

template<typename T>
AxisData<T> operator*(AxisData<T> lhs, const AxisData<T>& rhs) {
    return lhs *= rhs;
}
template<typename T>
AxisData<T> operator*(AxisData<T> lhs, T& k) {
    return lhs *= k;
}
