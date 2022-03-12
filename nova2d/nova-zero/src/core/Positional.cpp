#include "Positional.h"
#include "Game.h"
#include "../graphics/Drawable.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;

		Positional::Positional() 
		{
			m_ID = n2dGameGetID();
		};

		void Positional::LinkPositionalDrawable(Drawable* drawable)
		{
			m_Drawable = drawable;
			m_ID = n2dGameGetID();
		}

		float Positional::GetX() const { return (float)m_Position.x; }
		float Positional::GetY() const { return (float)m_Position.y; }
		Vec2Int Positional::GetPositionInt() const { return Vec2Int((int)m_Position.x, (int)m_Position.y); }
		Vec2 Positional::GetPosition() const { return Vec2((float)m_Position.x, (float)m_Position.y); }

		void Positional::SetX(float x)
		{
			m_Position.x = (int)x;
		}

		void Positional::SetY(float y)
		{
			m_Position.y = (int)y;
		}

		Vec2 Positional::GetCenter() { return m_Drawable->GetCenter(); }

		void Positional::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Positional::SetPositionInt(Vec2Int position)
		{
			m_Position = position;
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

			if (!m_Drawable)
			{
				LOG(LVL_NON_FATAL_ERROR, "Could not position positional. " + tostring(m_ID) + " has no Drawable.");
				return;
			}

			float x = (xR * Game::s_Width) - (m_Drawable->GetWidth() / 2);
			float y = (yR * Game::s_Height) - (m_Drawable->GetHeight() / 2);
						
			SetOffsetX((int)x);
			SetOffsetY((int)y);
		}
	}
}