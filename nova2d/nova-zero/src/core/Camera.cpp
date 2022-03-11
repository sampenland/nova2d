#include "Camera.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Camera::Camera(Vec2 startPos, Rect bounds)
		{
			m_ID = n2dGameGetID();

			SetPosition(startPos);

			if (bounds.x == 0 && bounds.y == 0 && bounds.w == 0 && bounds.h == 0)
			{
				SetMoveBounds(Game::GetGameBounds());
			}
			else
			{
				SetMoveBounds(bounds);
			}

			ConfigureUsingBounds(true, false);

			m_CleanID = n2dAddUpdater(Camera::Update, this);

		}

		void Camera::Update()
		{
			if (m_FreeMove)
				FreeMove();
		}

		void Camera::FreeMove()
		{
			if (n2dIsKeyDown(SDLK_w))
			{
				SetY(GetY() - 1.5f);
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				SetY(GetY() + 1.5f);
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				SetX(GetX() - 1.5f);
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				SetX(GetX() + 1.5f);
			}
		}

		void Camera::MoveX(float deltaX)
		{
			if (!IsWithinMoveBounds(GetX() + deltaX, GetY())) return;
			SetX(GetX() + deltaX);
		}

		void Camera::MoveY(float deltaY)
		{
			if (!IsWithinMoveBounds(GetX(), GetY() + deltaY)) return;
			SetY(GetY() + deltaY);
		}

		void Camera::DestroySelf()
		{
			n2dRemoveUpdater(m_CleanID);
		}
	}
}