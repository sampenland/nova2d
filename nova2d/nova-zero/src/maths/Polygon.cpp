#include "Polygon.h"

namespace novazero
{
	namespace maths
	{
		// Basic Rect constructor
		Polygon::Polygon(float x, float y, float width, float height)
		{
			m_Points.push_back(Vec2(x, y));
			m_Points.push_back(Vec2(x + width, y));
			m_Points.push_back(Vec2(x + width, y + height));
			m_Points.push_back(Vec2(x, y + height));
		}

		// Complex polygon constructor
		Polygon::Polygon(std::vector<Vec2> points)
		{
			m_Points = points;
		}

		int Polygon::Size() const
		{
			return m_Points.size();
		}

		bool Polygon::PointInPolygon(const Vec2& point, Polygon polygon)
		{
			Vec2* V = &polygon.m_Points[0];

			// 1 == inside, 0 == outside
			return CrossingNumber(point, V, polygon.Size()) == 1;
		}

		int Polygon::IsLeft(const Vec2& P0, const Vec2& P1, const Vec2& P2)
		{
			return ((P1.x - P0.x) * (P2.y - P0.y)
				- (P2.x - P0.x) * (P1.y - P0.y));
		}

		int Polygon::CrossingNumber(const Vec2& P, const Vec2* V, const int n)
		{

			int cn = 0;    // the  crossing number counter

			// loop through all edges of the polygon
			for (int i = 0; i < n; i++)
			{
				// edge from V[i]  to V[i+1]
				if (
					((V[i].y <= P.y) && (V[i + 1].y > P.y)) ||    // an upward crossing
					((V[i].y > P.y) && (V[i + 1].y <= P.y)) // a downward crossing
					)
				{
					// compute  the actual edge-ray intersect x-coordinate
					float vt = (float)(P.y - V[i].y) / (V[i + 1].y - V[i].y);

					// P.x < intersect
					if (P.x < V[i].x + vt * (V[i + 1].x - V[i].x))
					{
						++cn;   // a valid crossing of y=P.y right of P.x
					}
				}
			}

			return (cn & 1);    // 0 if even (out), and 1 if  odd (in)

		}
	}
}