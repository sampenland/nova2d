#pragma once
#include <vector>
#include "Vec2.h"

namespace novazero
{
	namespace maths
	{
		class Polygon
		{

		public:

			std::vector<Vec2> m_Points;

			// Basic Rect constructor
			Polygon(float x, float y, float width, float height);

			// Complex polygon constructor
			Polygon(std::vector<Vec2> points);

			int Size() const;

			static bool PointInPolygon(const Vec2& point, Polygon polygon);

		private:

			static int IsLeft(const Vec2& P0, const Vec2& P1, const Vec2& P2);
			static int CrossingNumber(const Vec2& P, const Vec2* V, const int n);
			
		};
	}
}