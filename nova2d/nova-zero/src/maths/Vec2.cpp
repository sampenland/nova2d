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

			if (mag == 0)
			{
				x = 0;
				y = 0;
				return *this;
			}

			x /= mag;
			y /= mag;

			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
		{
			stream << "Vec2 [" << vector.x << ", " << vector.y << "]";
			return stream;
		}

		float Vec2::LookAtAngle(Vec2 a, Vec2 b, float degExtraRotate)
		{
			float angle = AngleFromToTarget(a, b);
			return angle + degExtraRotate;
		}

		Vec2 Vec2::LookAtVec(Vec2 from, Vec2 to, bool normalize)
		{
			Vec2 v = to;
			v.subtract(from);
			
			if(normalize)
				v.normalize();
			
			return v;
		}

		Vec2 Vec2::VectorStepping(Vec2 currentPosition, Vec2 directionNormalized, float speed)
		{
			directionNormalized.multiply(Vec2(speed * n2dTimeScale, speed * n2dTimeScale));
			currentPosition.add(directionNormalized);
			return currentPosition;
		}
		
		Vec2 Vec2::VectorStepping(Vec2 currentPosition, float angle, float speed)
		{
			Vec2 directionNormalized = Vec2::UnitVec2FromAngle(angle);
			currentPosition.add(directionNormalized.multiply(Vec2(speed * n2dTimeScale, speed * n2dTimeScale)));
			return currentPosition;
		}

		Vec2 Vec2::UnitVec2FromAngle(float degrees)
		{
			/*
				Angles:

				    90
				180     0
				    270
			*/

			if (degrees > 360)
				degrees = std::fmod(degrees, 360);

			Vec2 unitVec;
			float rad = n2dDegToRad(degrees);
			unitVec.x = cos(rad);
			unitVec.y = sin(rad);
			return unitVec;
		}

		float Vec2::AngleFromVec2(Vec2 vec)
		{
			vec.y *= -1; // In engine, -1 point UP so invert Y

			if (vec.x == 0) // special cases
				return (vec.y > 0) ? 90
				: (vec.y == 0) ? 0
				: 270;
			else if (vec.y == 0) // special cases
				return (vec.x >= 0) ? 0
				: 180;

			int ret = n2dRadToDeg(atanf((float)vec.y / vec.x));

			if (vec.x < 0 && vec.y < 0) // quadrant Ⅲ
				ret = 180 + ret;
			else if (vec.x < 0) // quadrant Ⅱ
				ret = 180 + ret; // it actually substracts
			else if (vec.y < 0) // quadrant Ⅳ
				ret = 270 + (90 + ret); // it actually substracts
			return ret;
		}

		float Vec2::AngleFromToTarget(Vec2 position, Vec2 target)
		{
			Vec2 pN = position.normalize();
			Vec2 v = target.normalize();
			v.subtract(pN);
			return AngleFromVec2(v);
		}

		Vec2 Vec2::Random(float minX, float maxX, float minY, float maxY)
		{
			Vec2 v;
			v.x = n2dRandomFloat(minX, maxX);
			v.y = n2dRandomFloat(minY, maxY);
			return v;
		}

		Vec2 Vec2::Random(Vec2 min, Vec2 max)
		{
			Vec2 v;
			v.x = n2dRandomFloat(min.x, max.x);
			v.y = n2dRandomFloat(min.y, max.y);
			return v;
		}
	}
}