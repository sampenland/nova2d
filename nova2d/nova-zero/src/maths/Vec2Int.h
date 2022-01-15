#pragma once
#include <iostream>

namespace novazero
{
	namespace maths
	{
		struct Vec2Int
		{
			int x, y;

			Vec2Int();
			Vec2Int(const int& x, const int& y);

			Vec2Int& add(const Vec2Int& other);
			Vec2Int& subtract(const Vec2Int& other);
			Vec2Int& multiply(const Vec2Int& other);
			Vec2Int& divide(const Vec2Int& other);

			friend Vec2Int operator+(Vec2Int left, Vec2Int& right);
			friend Vec2Int operator-(Vec2Int left, Vec2Int& right);
			friend Vec2Int operator*(Vec2Int left, Vec2Int& right);
			friend Vec2Int operator/(Vec2Int left, Vec2Int& right);

			Vec2Int& operator+=(const Vec2Int& other);
			Vec2Int& operator-=(const Vec2Int& other);
			Vec2Int& operator*=(const Vec2Int& other);
			Vec2Int& operator/=(const Vec2Int& other);

			bool operator==(const Vec2Int& other);
			bool operator!=(const Vec2Int& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec2Int& vector);

		};
	}
}