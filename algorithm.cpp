#pragma once


template<typename T, typename U, typename V>
T clamp(const T& value, const U& low, const V& high) {
    if (value < static_cast<T>(low)) {
        return static_cast<T>(low);
    }
    else if (value > static_cast<T>(high)) {
        return static_cast<T>(high);
    }
    else {
        return value;
    }
}
