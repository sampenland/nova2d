#pragma once
#include <iostream>

namespace novazero
{
	namespace maths
	{
		struct Vec2
		{
			float x, y;

			Vec2();
			Vec2(const float& x, const float& y);

			Vec2& add(const Vec2& other);
			Vec2& subtract(const Vec2& other);
			Vec2& multiply(const Vec2& other);
			Vec2& divide(const Vec2& other);

			friend Vec2 operator+(Vec2 left, Vec2& right);
			friend Vec2 operator-(Vec2 left, Vec2& right);
			friend Vec2 operator*(Vec2 left, Vec2& right);
			friend Vec2 operator/(Vec2 left, Vec2& right);

			Vec2& operator+=(const Vec2& other);
			Vec2& operator-=(const Vec2& other);
			Vec2& operator*=(const Vec2& other);
			Vec2& operator/=(const Vec2& other);

			bool operator==(const Vec2& other);
			bool operator!=(const Vec2& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);

			static float LookAtAngle(Vec2 a, Vec2 b, float degExtraRotate)
			{
				double angle = atan2(b.y - a.y, b.x - a.x);
				return (float)floor((angle * (180.0 / 3.141592653589793238463))) + degExtraRotate;
			}

		};
	}
}