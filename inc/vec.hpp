#pragma once

#include <exception>
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

template <std::size_t N, typename T = float>
struct vec
{
    T data[N] = {};

    std::size_t size() const {return (N);}

    vec() : vec(0) {}
    vec(T f) {for (std::size_t i = 0; i < N; i++) data[i] = f;}
    vec(T x, T y) requires (N >= 2) : vec() {data[0] = x; data[1] = y;}
    vec(T x, T y, T z) requires (N >= 3) : vec() {data[0] = x; data[1] = y; data[2] = z;}
    vec(T x, T y, T z, T w) requires (N >= 4) : vec() {data[0] = x; data[1] = y; data[2] = z; data[3] = w;}
    vec(std::initializer_list<T> values)
    {
        if (values.size() > N)
            throw std::runtime_error("vec: too many values");

        std::size_t i = 0;
        for (const T& v : values)
            data[i++] = v;
    }

    template <std::size_t NN, typename TT>
    vec(const vec<NN, TT>& cpy) {for (std::size_t i = 0; i < std::min(N, NN); i++) data[i] = cpy.data[i];}
    ~vec() = default;

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
    vec<N, T>&  scl(const vec<N, T>& b) {return (*this *= b);}

    vec<N, T>   operator/(const vec<N, T>& b) const;
    vec<N, T>&  operator/=(const vec<N, T>& b);
    vec<N, T>&  div(const vec<N, T>& b) {return (*this /= b);}

    static vec<N, T>   linear_combination(const std::vector<vec<N, T>>& vecs, const std::vector<T>& scls)
    {
        if (vecs.size() != scls.size())
            throw std::runtime_error("arrays wrong size");

        vec<N, T>   res;

        for (std::size_t i = 0; i < vecs.size(); i++)
            for (std::size_t j = 0; j < N; j++)
                res.data[j] = std::fma(vecs[i].data[j], scls[i], res.data[j]);

        return (res);
    }

	static constexpr T	length(const vec<N, T>& v)
	{
		T	acc = 0;

		for (std::size_t i = 0; i < N; i++)
			acc += v.data[i] * v.data[i];

		return (std::sqrt(acc));
	}

	constexpr T	length() const {return (vec<N, T>::length(*this));}

	constexpr T	norm_1() const {throw std::logic_error("vec::norm_1 not implemented");}
	constexpr T	norm() const {throw std::logic_error("vec::norm not implemented");}
	constexpr T	norm_inf() const {throw std::logic_error("vec::norm_inf not implemented");}

	static constexpr T	angle_cos(const vec<N, T>& v1, const vec<N, T>& v2) {(void)v1; (void)v2; throw std::logic_error("vec::angle_cos not implemented");}
	constexpr T	angle_cos(const vec<N, T>& v) const {return (vec<N, T>::angle_cos(*this, v));}

	static constexpr T distance(const vec<N, T>& v1, const vec<N, T>& v2)
	{
		T value = 0.0;

		for (std::size_t i = 0; i < N; i++)
			value += (v1.data[i] - v2.data[i]) * (v1.data[i] - v2.data[i]);

		return (std::sqrt(value));
	}

	constexpr T	distance(const vec<N, T>& v) const
	{
		return (vec<N, T>::distance(*this, v));
	}

	static constexpr vec<N, T>	normalize(const vec<N, T>& v)
	{
		T	len = v.length();

		return (len > 0 ? v / len : vec<N, T>(0));
	}
	constexpr vec<N, T>	normalize() const {return (vec<N, T>::normalize(*this));}

	static constexpr vec<N, T>	cross(const vec<N, T>& v1, const vec<N, T>& v2) requires (N == 3)
	{
		return (vec<N, T>(
			v1.y() * v2.z() - v1.z() * v2.y(),
			v1.z() * v2.x() - v1.x() * v2.z(),
			v1.x() * v2.y() - v1.y() * v2.x()
		));
	}
	constexpr vec<N, T>	cross(const vec<N, T>& v) const requires (N == 3) {return (vec<N, T>::cross(*this, v));}

	static constexpr T	dot(const vec<N, T>& v1, const vec<N, T>& v2)
	{
		T	acc = 0;

		for (std::size_t i = 0; i < N; i++)
			acc += v1.data[i] * v2.data[i];

		return (acc);
	}
	constexpr T	dot(const vec<N, T>& v) const {return (vec<N, T>::dot(*this, v));}

	static constexpr vec<N, T>	reflect(const vec<N, T>& v, const vec<N, T>& n)
	{
		return (v - vec<N, T>(2.0) * vec<N, T>(dot(n, v)) * n);
	}
	constexpr vec<N, T>	reflect(const vec<N, T>& n) const {return (vec<N, T>::reflect(*this, n));}

    constexpr T&  x() requires (N >= 1) {return (data[0]);}
    constexpr T&  y() requires (N >= 2) {return (data[1]);}
    constexpr T&  z() requires (N >= 3) {return (data[2]);}
    constexpr T&  w() requires (N >= 4) {return (data[3]);}

    constexpr T&  r() requires (N >= 1) {return (data[0]);}
    constexpr T&  g() requires (N >= 2) {return (data[1]);}
    constexpr T&  b() requires (N >= 3) {return (data[2]);}
    constexpr T&  a() requires (N >= 4) {return (data[3]);}

    constexpr T   x() const requires (N >= 1) {return (data[0]);}
    constexpr T   y() const requires (N >= 2) {return (data[1]);}
    constexpr T   z() const requires (N >= 3) {return (data[2]);}
    constexpr T   w() const requires (N >= 4) {return (data[3]);}

    constexpr T   r() const requires (N >= 1) {return (data[0]);}
    constexpr T   g() const requires (N >= 2) {return (data[1]);}
    constexpr T   b() const requires (N >= 3) {return (data[2]);}
    constexpr T   a() const requires (N >= 4) {return (data[3]);}
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
