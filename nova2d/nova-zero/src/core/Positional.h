#pragma once
#include "../maths/Vec2.h"

namespace novazero
{
	namespace core
	{
		class Positional
		{

		protected:
			float m_X = 0;
			float m_Y = 0;
			float m_Angle = 0;

		public:

			Positional() {};

			float GetX() const { return m_X; }
			float GetY() const { return m_Y; }
			float GetAngle() const { return m_Angle; }

			void SetX(float x)
			{
				m_X = x;
			}
			
			void SetY(float y)
			{
				m_Y = y;
			}

			void SetAngle(float a)
			{
				m_Angle = a;
			}

		};
	}
}