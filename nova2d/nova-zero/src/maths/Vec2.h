#pragma once
#include <iostream>
#include "Box2D/Box2D.h"

#ifdef NOVA_EMSCRIPTEN
	#include <cmath>
#endif

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
			Vec2& scale(const float mag);

			Vec2& normalize();

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

			static float LookAtAngle(Vec2 a, Vec2 b, float degExtraRotate = 0);
			static Vec2 LookAtVec(Vec2 from, Vec2 to, bool normalize = false);

			static Vec2 VectorStepping(Vec2 currentPosition, Vec2 directionNormalized, float speed);
			static Vec2 VectorStepping(Vec2 currentPosition, float angle, float speed);

			static Vec2 UnitVec2FromAngle(float degrees);
			static float AngleFromVec2(Vec2 vec);
			static float AngleFromToTarget(Vec2 position, Vec2 target, float extraDegrees = 0.f);

			static float Distance(Vec2 a, Vec2 b)
			{
				Vec2 m = b.subtract(a);
				float mag = (float)std::sqrt((std::pow(m.x, 2) + std::pow(m.y, 2)));
				return mag;
			}

			static Vec2 Random(float minX, float maxX, float minY, float maxY);
			static Vec2 Random(Vec2 min, Vec2 max);

		};
	}
}