#pragma once
#include "../maths/Vec2.h"

namespace novazero
{
	namespace core
	{
		class Positional
		{

		protected:
			int m_X = 0;
			int m_Y = 0;
			int m_Angle = 0;

		public:

			Positional() {};

			int GetX() const { return m_X; }
			int GetY() const { return m_Y; }
			int GetAngle() const { return m_Angle; }

			void SetX(int x)
			{
				m_X = x;
			}
			
			void SetY(int y)
			{
				m_Y = y;
			}

			void SetAngle(int a)
			{
				m_Angle = a;
			}

		};
	}
}