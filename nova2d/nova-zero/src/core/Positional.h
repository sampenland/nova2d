#pragma once
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace core
	{
		using namespace maths;

		class Positional
		{

		protected:
			
			Vec2Int m_Position;
			int m_Angle = 0;

		public:

			Positional() {};

			int GetX() const { return m_Position.x; }
			int GetY() const { return m_Position.y; }
			Vec2Int GetPosition() const { return m_Position; }
			int GetAngle() const { return m_Angle; }

			void SetX(int x)
			{
				m_Position.x = x;
			}
			
			void SetY(int y)
			{
				m_Position.y = y;
			}

			void SetPosition(Vec2Int position)
			{
				m_Position = position;
			}

			void SetAngle(int a)
			{
				m_Angle = a;
			}

		};
	}
}