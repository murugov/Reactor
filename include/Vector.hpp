#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>
#include <array>
#include <optional>
#include <raylib.h>

namespace Math {

template <typename T, size_t N>
class Vector {
private:
    std::array<T, N> data_{};
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Vector() = default;
    
    Vector(std::initializer_list<T> list) {
        size_t i = 0;
        for (const T& elem : list) {
            if (i >= N) break;
            data_[i++] = elem;
        }
    }
       
    // --- Copy Constructor ---

    Vector(const Vector<T, N>& other) = default;

    // --- Move Constructor ---

    Vector(Vector<T, N>&& other) noexcept = default;

    // --- Copy Assignment Operator ---

    Vector<T, N>& operator=(const Vector<T, N>& other) = default;

    // --- Move Assignment Operator ---
    
    Vector<T, N>& operator=(Vector<T, N>&& other) noexcept = default;

    // --- Destructor ---

    ~Vector() =default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    T x() const { return data_[0]; }
    T y() const { static_assert(N >= 2, "Vector must be 2D or higher"); return data_[1]; } 
    T z() const { static_assert(N >= 3, "Vector must be 3D or higher"); return data_[2]; }
    T w() const { static_assert(N >= 4, "Vector must be 4D or higher"); return data_[3]; } 

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void set_x(const T& val) { data_[0] = val; }
    void set_y(const T& val) { static_assert(N >= 2, "Vector must be 2D or higher"); data_[1] = val; } 
    void set_z(const T& val) { static_assert(N >= 3, "Vector must be 3D or higher"); data_[2] = val; }
    void set_w(const T& val) { static_assert(N >= 4, "Vector must be 4D or higher"); data_[3] = val; } 

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void print () const;

    Vector<T, N> add (const Vector<T, N>& other) const;
    Vector<T, N> sub (const Vector<T, N>& other) const;
    Vector<T, N> mul (T factor) const;

    double len () const;
    double dot (const Vector<T, N>& other) const;

    // -------------------------------------------------------------------------------
    // --- Operators Prototypes ---

    std::optional<T> operator[](const size_t i) const;

    Vector<T, N>     operator + (const Vector<T, N>& other);
    Vector<T, N>     operator - (const Vector<T, N>& other);
    Vector<T, N>     operator * (T factor);
    T                operator ^ (const Vector<T, N>& other);

    Vector<T, N>&    operator += (const Vector<T, N>& other);
    Vector<T, N>&    operator -= (const Vector<T, N>& other);
    Vector<T, N>&    operator *= (T factor);

    // -------------------------------------------------------------------------------
    // --- Implementation Of Operators ---

    friend std::ostream& operator << (std::ostream& os, const Vector<T, N>& v) {
        os << "(";
        for (size_t i = 0; i < N - 1; ++i) {
            os << v.data_[i];
            os << ", ";
        }
        os << v.data_[N - 1];
        os << ")";

        return os;
    }
};

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

template <typename T, size_t N>
void Vector<T, N>::print () const {
    std::cout << *this << std::endl;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::add (const Vector<T, N>& other) const {
    Vector<T, N> sum {};

    for (size_t i = 0; i < N; ++i) {
        sum.data_[i] = this->data_[i] + other.data_[i];
    }
    return sum;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::sub (const Vector<T, N>& other) const {
    Vector<T, N> diff {};

    for (size_t i = 0; i < N; ++i) {
        diff.data_[i] = this->data_[i] - other.data_[i];
    }
    return diff;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::mul (T factor) const {
    Vector<T, N> prod {};

    for (size_t i = 0; i < N; ++i) {
        prod.data_[i] = this->data_[i] * factor;
    }
    return prod;
}

template <typename T, size_t N>
double Vector<T, N>::len () const {  
    double len_sq = 0.0;

    for (size_t i = 0; i < N; ++i) {
        len_sq += this->data_[i] * this->data_[i];
    }
    return std::sqrt(len_sq);
}

template <typename T, size_t N>
double Vector<T, N>::dot (const Vector<T, N>& other) const {
    double dot_val = 0.0;

    for (size_t i = 0; i < N; ++i) {
        dot_val += this->data_[i] * other.data_[i];
    }
    return dot_val;
}

// -------------------------------------------------------------------------------
// --- Implementation Of Operators ---

template <typename T, size_t N>
std::optional<T> Vector<T, N>::operator [] (const size_t i) const {
    if (i >= N) {
        return std::nullopt;
    }

    return data_[i];
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator + (const Vector<T, N>& other) {
    return this->add(other);
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator - (const Vector<T, N>& other) {
    return this->sub(other);
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator * (T factor) {
    return this->mul(factor);
}

template <typename T, size_t N>
T Vector<T, N>::operator ^ (const Vector<T, N>& other) {
    return this->dot(other);
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator += (const Vector<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
        this->data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator -= (const Vector<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
        this->data_[i] -= other.data_[i];
    }
    return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator *= (T factor) {
    for (size_t i = 0; i < N; ++i) {
        this->data_[i] *= factor;
    }
    return *this;
}

using Vector2D = Vector<float, 2>;
using Vector3D = Vector<float, 3>;
using Vector4D = Vector<float, 4>;

}

#endif