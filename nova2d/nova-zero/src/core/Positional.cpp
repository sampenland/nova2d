#include "Positional.h"
#include "Game.h"
#include "../physics/PhySprite.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace physics;

		Positional::Positional() 
		{
			m_ID = n2dGameGetID();
		};

		void Positional::LinkPositionalDrawable(Drawable* drawable)
		{
			m_Drawable = drawable;
			m_ID = n2dGameGetID();
		}

		Sprite* Positional::GetSprite()
		{
			if(m_Drawable)
				return (Sprite*)m_Drawable;
			return nullptr;
		}

		PhySprite* Positional::GetPhySprite()
		{
			if(m_Drawable)
				return (PhySprite*)m_Drawable;
			return nullptr;
		}

		void Positional::SetFacing(Directions facing)
		{
			m_Facing = facing;
		}

		float Positional::GetX() const 
		{ 
			return (float)m_Position.x / CAMERA_ZOOM; 
		}

		float Positional::GetY() const 
		{ 
			return (float)m_Position.y / CAMERA_ZOOM; 
		}
		Vec2Int Positional::GetPositionInt() const 
		{
			return Vec2Int((int)m_Position.x, (int)m_Position.y); 
		}
		Vec2 Positional::GetPosition() const 
		{ 
			return Vec2(GetX(), GetY()); 
		}

		void Positional::SetX(float x)
		{
			m_Position.x = x * CAMERA_ZOOM;
		}

		void Positional::SetY(float y)
		{
			m_Position.y = y * CAMERA_ZOOM;
		}

		Vec2 Positional::GetWorldCenterPosition()
		{
			if (GetDrawable())
			{
				return Vec2(GetX() + GetDrawable()->GetWidth()/2, GetY() + GetDrawable()->GetHeight()/2);
			}
			return GetPosition();
		}

		Vec2 Positional::GetBottomRight()
		{
			if (GetDrawable())
			{
				return Vec2(GetX() + GetDrawable()->GetWidth(), GetY() + GetDrawable()->GetHeight());
			}
			return GetPosition();
		}

		void Positional::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Positional::SetPositionInt(Vec2Int position)
		{
			SetX((float)position.x);
			SetY((float)position.y);
		}

		void Positional::SetAngle(float a)
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
				LOG(LVL_NON_FATAL_ERROR, "Could not position positional. " + tostring(m_ID) + " has no Drawable.", __FILE__, __LINE__);
				return;
			}

			float x = (xR * Game::s_Width) - (m_Drawable->GetWidth() / 2);
			float y = (yR * Game::s_Height) - (m_Drawable->GetHeight() / 2);
						
			SetOffsetX(x);
			SetOffsetY(y);
		}
	}
}