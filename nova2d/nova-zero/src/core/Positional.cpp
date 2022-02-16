#include "Positional.h"
#include "Game.h"
#include "../graphics/Drawable.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;

		Positional::Positional() {};

		void Positional::LinkPositionalSprite(Sprite* sprite)
		{
			m_Sprite = sprite;
		}

		float Positional::GetX() const { return (float)m_Position.x; }
		float Positional::GetY() const { return (float)m_Position.y; }
		Vec2Int Positional::GetPositionInt() const { return Vec2Int((int)m_Position.x, (int)m_Position.y); }
		Vec2 Positional::GetPosition() const { return Vec2((float)m_Position.x, (float)m_Position.y); }

		int Positional::GetWidth() const { return m_Size.x; }
		int Positional::GetHeight() const { return m_Size.y; }
		void Positional::SetWidth(int w) { m_Size.x = w; }
		void Positional::SetHeight(int h) { m_Size.y = h; }
		Vec2Int Positional::GetSize() const { return Vec2Int(m_Size.x, m_Size.y); }
		
		Vec2 Positional::GetCenter() const 
		{ 
			return Vec2((float)m_Size.x / 2 + m_Position.x, (float)m_Size.y / 2 + m_Position.y);
		}

		int Positional::GetAngle() const { return m_Angle; }

		void Positional::SetX(float x)
		{
			m_Position.x = (int)x;
		}

		void Positional::SetY(float y)
		{
			m_Position.y = (int)y;
		}

		void Positional::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Positional::SetPositionInt(Vec2Int position)
		{
			m_Position = position;
		}

		void Positional::SetSize(Vec2Int size)
		{
			m_Size = size;
		}

		void Positional::SetAngle(int a)
		{
			m_Angle = a;
		}

		void Positional::SetPositionCenter()
		{
			SetPositionPercents(50, 50);
		}

		void Positional::SetPositionPercents(char xPercent, char yPercent)
		{
			float xR = (float)xPercent / 100.0f;
			float yR = (float)yPercent / 100.0f;

			float x = (xR * Game::s_Width) - (GetWidth() / 2);
			float y = (yR * Game::s_Height) - (GetHeight() / 2);

			SetPosition(Vec2(x, y));
		}
	}
}