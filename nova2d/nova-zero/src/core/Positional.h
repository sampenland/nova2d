#pragma once

namespace novazero
{
	namespace core
	{
		class Positional
		{

		private:
			float m_X = 0;
			float m_Y = 0;

		public:

			Positional() {};

			float GetX() const { return m_X; }
			float GetY() const { return m_Y; }

			void SetX(float x)
			{
				m_X = x;
			}
			
			void SetY(float y)
			{
				m_Y = y;
			}

		};
	}
}