#include "Vec2.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maths
	{
		using namespace core;

		Vec2::Vec2()
		{
			x = 0;
			y = 0;
		}

		Vec2::Vec2(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}

		Vec2& Vec2::add(const Vec2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vec2& Vec2::subtract(const Vec2& other)
		{
			// TODO: not sure if this works, along with add/mutl etc
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vec2& Vec2::multiply(const Vec2& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		Vec2& Vec2::scale(const float mag)
		{
			x *= mag;
			y *= mag;

			return *this;
		}

		Vec2& Vec2::divide(const Vec2& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		Vec2 operator+(Vec2 left, Vec2& right)
		{
			return left.add(right);
		}

		Vec2 operator-(Vec2 left, Vec2& right)
		{
			return left.subtract(right);
		}

		Vec2 operator*(Vec2 left, Vec2& right)
		{
			return left.multiply(right);
		}

		Vec2 operator/(Vec2 left, Vec2& right)
		{
			return left.divide(right);
		}

		Vec2& Vec2::operator+=(const Vec2& other)
		{
			return add(other);
		}

		Vec2& Vec2::operator-=(const Vec2& other)
		{
			return subtract(other);
		}

		Vec2& Vec2::operator*=(const Vec2& other)
		{
			return multiply(other);
		}

		Vec2& Vec2::operator/=(const Vec2& other)
		{
			return divide(other);
		}

		bool Vec2::operator==(const Vec2& other)
		{
			return x == other.x && y == other.y;
		}

		bool Vec2::operator!=(const Vec2& other)
		{
			return !(*this == other);
		}

		Vec2& Vec2::normalize()
		{
			float mag = (float)std::sqrt((std::pow(x, 2) + std::pow(y, 2)));
			
			x /= mag;
			y /= mag;

			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
		{
			stream << "Vec2 [" << vector.x << ", " << vector.y << "]";
			return stream;
		}

		Vec2 Vec2::UnitVec2FromAngle(float degrees)
		{
			Vec2 unitVec;
			float rad = n2dDegToRad(degrees);
			unitVec.x = cos(rad);
			unitVec.y = sin(rad);
			return unitVec;
		}
	}
}