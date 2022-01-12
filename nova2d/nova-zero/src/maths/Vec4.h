#pragma once
#include <iostream>

namespace novazero
{
	namespace maths
	{
		struct Vec4
		{
			float x, y, z, w;

			Vec4();
			Vec4(const float& x, const float& y, const float& z, const float& w);

			Vec4& add(const Vec4& other);
			Vec4& subtract(const Vec4& other);
			Vec4& multiply(const Vec4& other);
			Vec4& divide(const Vec4& other);

			friend Vec4 operator+(Vec4 left, Vec4& right);
			friend Vec4 operator-(Vec4 left, Vec4& right);
			friend Vec4 operator*(Vec4 left, Vec4& right);
			friend Vec4 operator/(Vec4 left, Vec4& right);

			Vec4& operator+=(const Vec4& other);
			Vec4& operator-=(const Vec4& other);
			Vec4& operator*=(const Vec4& other);
			Vec4& operator/=(const Vec4& other);

			bool operator==(const Vec4& other);
			bool operator!=(const Vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);

		};
	}
}