#pragma once

#include <iostream>
#include <vector>

template <std::size_t N, typename T = float>
struct vec
{
    T data[N] = {};

    std::size_t size() const {return (N);}

    vec() : vec(0) {}
    vec(float f) {for (std::size_t i = 0; i < N; i++) data[i] = f;}
    vec(float x, float y) requires (N >= 2) : vec() {data[0] = x; data[1] = y;}
    vec(float x, float y, float z) requires (N >= 3) : vec() {data[0] = x; data[1] = y; data[2] = z;}
    vec(float x, float y, float z, float w) requires (N >= 4) : vec() {data[0] = x; data[1] = y; data[2] = z; data[3] = w;}

    bool    operator==(const vec<N, T>& b) const;
    bool    operator!=(const vec<N, T>& b) const {return (!(*this == b));};

    vec<N, T>   operator-() const {return (*this * -1);}

    vec<N, T>   operator+(const vec<N, T>& b) const;
    vec<N, T>&  operator+=(const vec<N, T>& b);
    vec<N, T>&  add(const vec<N, T>& b) {return (*this += b);}

    vec<N, T>   operator-(const vec<N, T>& b) const;
    vec<N, T>&  operator-=(const vec<N, T>& b);
    vec<N, T>&  sub(const vec<N, T>& b) {return (*this -= b);}

    vec<N, T>   operator*(const vec<N, T>& b) const;
    vec<N, T>&  operator*=(const vec<N, T>& b);
    vec<N, T>&  mul(const vec<N, T>& b) {return (*this *= b);}

    vec<N, T>   operator/(const vec<N, T>& b) const;
    vec<N, T>&  operator/=(const vec<N, T>& b);
    vec<N, T>&  div(const vec<N, T>& b) {return (*this /= b);}

    vec<N, T>   operator*(const T& t) const;
    vec<N, T>&  operator*=(const T &t);
    vec<N, T>&  scl(const T& t) {return (*this *= t);}

    T&  x() requires (N >= 1) {return (data[0]);}
    T&  y() requires (N >= 2) {return (data[1]);}
    T&  z() requires (N >= 3) {return (data[2]);}
    T&  w() requires (N >= 4) {return (data[3]);}

    T&  r() requires (N >= 1) {return (data[0]);}
    T&  g() requires (N >= 2) {return (data[1]);}
    T&  b() requires (N >= 3) {return (data[2]);}
    T&  a() requires (N >= 4) {return (data[3]);}

    T   x() const requires (N >= 1) {return (data[0]);}
    T   y() const requires (N >= 2) {return (data[1]);}
    T   z() const requires (N >= 3) {return (data[2]);}
    T   w() const requires (N >= 4) {return (data[3]);}

    T   r() const requires (N >= 1) {return (data[0]);}
    T   g() const requires (N >= 2) {return (data[1]);}
    T   b() const requires (N >= 3) {return (data[2]);}
    T   a() const requires (N >= 4) {return (data[3]);}
};

template <std::size_t N, typename T>
std::ostream&   operator<<(std::ostream& s, const vec<N, T>& v)
{
    s << "[";
    for (std::size_t i = 0; i < N; i++)
    {
        s << v.data[i];
        if (i != N - 1)
            s << ", ";
    }
    s << "]";
    return (s);
}

using vec2i = vec<2, int>;
using vec3i = vec<3, int>;
using vec4i = vec<4, int>;

using vec2f = vec<2, float>;
using vec3f = vec<3, float>;
using vec4f = vec<4, float>;

using vec2d = vec<2, double>;
using vec3d = vec<3, double>;
using vec4d = vec<4, double>;

template <std::size_t N, typename T>
bool vec<N, T>::operator==(const vec<N, T>& b) const
{
    for (std::size_t i = 0; i < N; i++)
        if (data[i] != b.data[i])
            return false;
    return true;
}

template <std::size_t N, typename T>
vec<N, T>    vec<N, T>::operator+(const vec<N, T>& b) const
{
    vec<N, T>   res;

    for (std::size_t i = 0; i < N; i++)
        res.data[i] = data[i] + b.data[i];
    
    return (res);
}

template <std::size_t N, typename T>
vec<N, T>&  vec<N, T>::operator+=(const vec<N, T>& b)
{
    *this = *this + b;
    return (*this);
}

template <std::size_t N, typename T>
vec<N, T>    vec<N, T>::operator-(const vec<N, T>& b) const
{
    vec<N, T>   res;

    for (std::size_t i = 0; i < N; i++)
        res.data[i] = data[i] - b.data[i];
    
    return (res);
}

template <std::size_t N, typename T>
vec<N, T>&  vec<N, T>::operator-=(const vec<N, T>& b)
{
    *this = *this - b;
    return (*this);
}

template <std::size_t N, typename T>
vec<N, T>    vec<N, T>::operator*(const vec<N, T>& b) const
{
    vec<N, T>   res;

    for (std::size_t i = 0; i < N; i++)
        res.data[i] = data[i] * b.data[i];
    
    return (res);
}

template <std::size_t N, typename T>
vec<N, T>&  vec<N, T>::operator*=(const vec<N, T>& b)
{
    *this = *this * b;
    return (*this);
}

template <std::size_t N, typename T>
vec<N, T>    vec<N, T>::operator/(const vec<N, T>& b) const
{
    vec<N, T>   res;

    for (std::size_t i = 0; i < N; i++)
        res.data[i] = data[i] / b.data[i];
    
    return (res);
}

template <std::size_t N, typename T>
vec<N, T>&  vec<N, T>::operator/=(const vec<N, T>& b)
{
    *this = *this / b;
    return (*this);
}

template <std::size_t N, typename T>
vec<N, T>    vec<N, T>::operator*(const T& t) const
{
    vec<N, T>   res;

    for (std::size_t i = 0; i < N; i++)
        res.data[i] = data[i] * t;

    return (res);
}

template <std::size_t N, typename T>
vec<N, T>&  vec<N, T>::operator*=(const T &t)
{
    *this = *this * t;
    return (*this);
}
