#include "Vec2Int.h"

namespace novazero
{
	namespace maths
	{
		Vec2Int::Vec2Int()
		{
			x = 0;
			y = 0;
		}

		Vec2Int::Vec2Int(const int& x, const int& y)
		{
			this->x = x;
			this->y = y;
		}

		Vec2Int& Vec2Int::add(const Vec2Int& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vec2Int& Vec2Int::subtract(const Vec2Int& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vec2Int& Vec2Int::multiply(const Vec2Int& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		Vec2Int& Vec2Int::divide(const Vec2Int& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		Vec2Int operator+(Vec2Int left, Vec2Int& right)
		{
			return left.add(right);
		}

		Vec2Int operator-(Vec2Int left, Vec2Int& right)
		{
			return left.subtract(right);
		}

		Vec2Int operator*(Vec2Int left, Vec2Int& right)
		{
			return left.multiply(right);
		}

		Vec2Int operator/(Vec2Int left, Vec2Int& right)
		{
			return left.divide(right);
		}

		Vec2Int& Vec2Int::operator+=(const Vec2Int& other)
		{
			return add(other);
		}

		Vec2Int& Vec2Int::operator-=(const Vec2Int& other)
		{
			return subtract(other);
		}

		Vec2Int& Vec2Int::operator*=(const Vec2Int& other)
		{
			return multiply(other);
		}

		Vec2Int& Vec2Int::operator/=(const Vec2Int& other)
		{
			return divide(other);
		}

		bool Vec2Int::operator==(const Vec2Int& other)
		{
			return x == other.x && y == other.y;
		}

		bool Vec2Int::operator!=(const Vec2Int& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2Int& vector)
		{
			stream << "Vec2Int [" << vector.x << ", " << vector.y << "]";
			return stream;
		}
	}
}