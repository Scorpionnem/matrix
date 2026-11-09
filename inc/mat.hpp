#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include "math.hpp"

/*
	column major, C columns * R rows

	3*3 matrix

	0 1 2
	3 4 5 -> 0 3 6  1 4 7  2 5 8
	6 7 8

	4*4 matirx
	0  1  2  3
	4  5  6  7  -> 0 4 8 12  1 5 9 13  2 6 10 14  3 7 11 15
	8  9  10 11
	12 13 14 15

	horizontal = row
	vertical = column
*/

template <std::size_t C, std::size_t R, typename T = float>
struct	mat
{
	T	data[C * R] = {};

	mat() {}

	mat(std::initializer_list<vec<C, T>> rows)
	{
		if (rows.size() != R)
			throw std::runtime_error("mat: wrong number of rows");

		std::size_t	row = 0;
		for (const vec<C, T>& v : rows)
		{
			for (std::size_t col = 0; col < C; col++)
				(*this)(col, row) = v.data[col];
			row++;
		}
	}

	std::size_t	cols() const {return (C);}
	std::size_t	rows() const {return (R);}

	static mat	identity() requires (C == R)
	{
		mat	res;

		for (std::size_t i = 0; i < C; i++)
			res(i, i) = 1;

		return (res);
	}

	mat		operator+(const mat& m) const {(void)m; throw std::logic_error("mat::operator+ not implemented");}
	mat&	operator+=(const mat& m) {(void)m; throw std::logic_error("mat::operator+= not implemented");}
	mat&	add(const mat& m) {return (*this += m);}

	mat		operator-(const mat& m) const {(void)m; throw std::logic_error("mat::operator- not implemented");}
	mat&	operator-=(const mat& m) {(void)m; throw std::logic_error("mat::operator-= not implemented");}
	mat&	sub(const mat& m) {return (*this -= m);}

	mat		operator*(T s) const {(void)s; throw std::logic_error("mat::operator*(scalar) not implemented");}
	mat&	operator*=(T s) {(void)s; throw std::logic_error("mat::operator*=(scalar) not implemented");}
	mat&	scl(T s) {return (*this *= s);}

	vec<R, T>	operator*(const vec<C, T>& v) const {(void)v; throw std::logic_error("mat::operator*(vec) not implemented");}

	template <std::size_t K>
	mat<K, R, T>	operator*(const mat<K, C, T>& m) const
	{
		mat<K, R, T>	res;

		for (std::size_t col = 0; col < K; col++)
		{
			for (std::size_t row = 0; row < R; row++)
			{
				for (std::size_t k = 0; k < C; k++)
					res(col, row) += (*this)(k, row) * m(col, k);
			}
		}

		return (res);
	}

	T	trace() const requires (C == R) {throw std::logic_error("mat::trace not implemented");}

	mat<R, C, T>	transpose() const {throw std::logic_error("mat::transpose not implemented");}

	mat	row_echelon() const {throw std::logic_error("mat::row_echelon not implemented");}

	T	determinant() const requires (C == R) {throw std::logic_error("mat::determinant not implemented");}

	mat	inverse() const requires (C == R) {throw std::logic_error("mat::inverse not implemented");}

	std::size_t	rank() const {throw std::logic_error("mat::rank not implemented");}

	static mat	translate(const vec<3, T> &v) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();

		res(3, 0) = v.x();
		res(3, 1) = v.y();
		res(3, 2) = v.z();
		return (res);
	}
	static mat	translate(const vec<2, T> &v) requires (C == 3 && R == 3)
	{
		mat	res = mat::identity();

		res(2, 0) = v.x();
		res(2, 1) = v.y();
		return (res);
	}

	static mat	scale(const vec<3, T> &v) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();

		res(0, 0) = v.x();
		res(1, 1) = v.y();
		res(2, 2) = v.z();
		return (res);
	}
	static mat	scale(const vec<2, T> &v) requires (C == 3 && R == 3)
	{
		mat	res = mat::identity();

		res(0, 0) = v.x();
		res(1, 1) = v.y();
		return (res);
	}

	static mat	rotateX(T angle) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();
		T c = std::cos(angle);
		T s = std::sin(angle);

		res(1, 1) =  c;
		res(1, 2) =  s;
		res(2, 1) = -s;
		res(2, 2) =  c;
		return (res);
	}

	static mat	rotateY(T angle) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();
		T c = std::cos(angle);
		T s = std::sin(angle);

		res(0, 0) =  c;
		res(0, 2) = -s;
		res(2, 0) =  s;
		res(2, 2) =  c;
		return (res);
	}

	static mat	rotateZ(T angle) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();
		T c = std::cos(angle);
		T s = std::sin(angle);

		res(0, 0) =  c;
		res(0, 1) =  s;
		res(1, 0) = -s;
		res(1, 1) =  c;
		return (res);
	}

	static mat	rotate(T angle) requires (C == 3 && R == 3)
	{
		mat	res = mat::identity();
		T c = std::cos(angle);
		T s = std::sin(angle);

		res(0, 0) =  c;
		res(0, 1) =  s;
		res(1, 0) = -s;
		res(1, 1) =  c;
		return (res);
	}

	static mat	perspective(T fov_deg, T aspect, T near, T far) requires (C == 4 && R == 4)
	{
		T	tf2 = std::tan(radians(fov_deg) / 2);

		mat	res;

		res(0, 0) = 1 / (aspect * tf2);
		res(1, 1) = 1 / tf2;
		res(2, 2) = -((far + near) / (far - near));
		res(3, 2) = -((2 * far * near) / (far - near));
		res(2, 3) = -1;
		return (res);
	}
	static mat	ortho(T left, T right, T bottom, T top, T near, T far) requires (C == 4 && R == 4)
	{
		mat	res = mat::identity();

		res(0, 0) = 2 / (right - left);
		res(1, 1) = 2 / (top - bottom);
		res(2, 2) = -2 / (far - near);

		res(3, 0) = -((right + left) / (right - left));
		res(3, 1) = -((top + bottom) / (top - bottom));
		res(3, 2) = -((far + near) / (far - near));

		return (res);
	}

	static mat	lookAt(const vec<3, T> &eye, const vec<3, T> &center, const vec<3, T> &up) requires (C == 4 && R == 4)
	{
		vec<3, T>	f = (center - eye).normalize();
		vec<3, T>	s = f.cross(up).normalize();
		vec<3, T>	u = s.cross(f);

		mat	res = mat::identity();

		res(0, 0) =  s.x();
		res(1, 0) =  s.y();
		res(2, 0) =  s.z();

		res(0, 1) =  u.x();
		res(1, 1) =  u.y();
		res(2, 1) =  u.z();

		res(0, 2) = -f.x();
		res(1, 2) = -f.y();
		res(2, 2) = -f.z();

		res(3, 0) = -s.dot(eye);
		res(3, 1) = -u.dot(eye);
		res(3, 2) =  f.dot(eye);
		return (res);
	}

	T	&operator()(std::size_t col, std::size_t row)
	{
		return (data[row + col * R]);
	}
	T	operator()(std::size_t col, std::size_t row) const
	{
		return (data[row + col * R]);
	}
};

template <std::size_t C, std::size_t R, typename T>
std::ostream&   operator<<(std::ostream& s, const mat<C, R, T>& m)
{
	for (std::size_t row = 0; row < R; row++)
	{
		s << "[";
		for (std::size_t col = 0; col < C; col++)
		{
			s << m(col, row);
			if (col != C - 1)
				s << ", ";
		}
		s << "]";
		if (row != R - 1)
			s << '\n';
	}
	return (s);
}

using mat2f = mat<2, 2, float>;
using mat3f = mat<3, 3, float>;
using mat4f = mat<4, 4, float>;
