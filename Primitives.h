#pragma once

#include <iostream>
#include <initializer_list>
#include <cmath> // For sqrt in magnitude calculation

template <typename T, size_t N>
class MathVector {
protected:
    T data[N]{}; // Initialize raw array with default values

public:
    // Default constructor
    MathVector() = default;

    // Constructor with initializer list
    MathVector(std::initializer_list<T> init) {
        size_t i = 0;
        for (const auto& val : init) {
            if (i < N)
                data[i++] = val;
        }
    }

    // Copy constructor
    MathVector(const MathVector& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] = other.data[i];
    }

    // Move constructor
    MathVector(MathVector&& other) noexcept {
        for (size_t i = 0; i < N; ++i)
            data[i] = std::move(other.data[i]);
    }

    // Copy assignment
    MathVector& operator=(const MathVector& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Move assignment
    MathVector& operator=(MathVector&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < N; ++i)
                data[i] = std::move(other.data[i]);
        }
        return *this;
    }

    // Access element
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    // Scalar multiplication
    MathVector operator*(T scalar) const {
        MathVector result;
        for (size_t i = 0; i < N; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    // Scalar division
    MathVector operator/(T scalar) const {
        MathVector result;
        for (size_t i = 0; i < N; ++i)
            result.data[i] = data[i] / scalar;
        return result;
    }

    // Dot product
    T dot(const MathVector& other) const {
        T result = T();
        for (size_t i = 0; i < N; ++i)
            result += data[i] * other.data[i];
        return result;
    }

    // Cross product (valid only for 3D vectors)
    MathVector cross(const MathVector& other) const {
        static_assert(N == 3, "Cross product is only defined for 3D vectors.");
        return MathVector{
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0]
        };
    }

    // Magnitude
    T magnitude() const {
        T result = T();
        for (size_t i = 0; i < N; ++i)
            result += data[i] * data[i];
        return std::sqrt(result);
    }

    // Normalize
    MathVector normalize() const {
        T mag = magnitude();
        return *this / mag;
    }

    // Equality check
    bool operator==(const MathVector& other) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    // In-place addition
    MathVector& operator+=(const MathVector& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] += other.data[i];
        return *this;
    }

    // In-place subtraction
    MathVector& operator-=(const MathVector& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] -= other.data[i];
        return *this;
    }

    // Addition
    MathVector operator+(const MathVector& other) const {
        MathVector result(*this);
        result += other;
        return result;
    }

    // Subtraction
    MathVector operator-(const MathVector& other) const {
        MathVector result(*this);
        result -= other;
        return result;
    }

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const MathVector& vec) {
        os << "{ ";
        for (size_t i = 0; i < N; ++i)
            os << vec.data[i] << (i < N - 1 ? ", " : " ");
        os << "}";
        return os;
    }

    template <typename U>
    operator MathVector<U, N>() const {
        MathVector<U, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = static_cast<U>(data[i]);
        return result;
    }

    template <typename U>
    MathVector(const MathVector<U, N>& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] = static_cast<T>(other[i]);
    }

    template <typename T, size_t N>
    MathVector<T, N> box(const MathVector<T, N>& minPos, const MathVector<T, N>& maxPos) const {
        MathVector<T, N> result = *this;
        for (size_t i = 0; i < N; ++i) {
            if (result[i] < minPos[i]) {
                result[i] = minPos[i];
            }
            else if (result[i] > maxPos[i]) {
                result[i] = maxPos[i];
            }
        }
        return result;
    }

    template <typename T, size_t N>
    MathVector<T, N> box(const MathVector<T, N>& maxPos) const {
        // Call the first version with (0, 0) as the min position and the provided max position
        return box(zero, maxPos);
    }

    static const MathVector zero;
};

template <typename T, size_t N>
const MathVector<T, N> MathVector<T, N>::zero{};


enum { X, Y, Z, W };

template <typename T>
using Vec3D = MathVector<T, 3>;

template <typename T>
using Vec2D = MathVector<T, 2>;

template <typename T>
using Twist = MathVector<T, 4>;

using IntTwist = Twist<int32_t>;

using Pos = MathVector<float, 4>;

using Velocity = Pos;

using Acceleration = Pos;


