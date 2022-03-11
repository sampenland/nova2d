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

			m_CleanID = n2dAddUpdaterPersistent(Camera::Update, this);

		}

		void Camera::Update()
		{
			if (m_FreeMove)
				FreeMove();
		}

		void Camera::FreeMove()
		{
			float speed = 1.5f;

			if (n2dIsKeyDown(SDLK_LSHIFT))
			{
				speed *= 4.f;
			}

			if (n2dIsKeyDown(SDLK_w))
			{
				SetY(GetY() + speed);
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				SetY(GetY() - speed);
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				SetX(GetX() + speed);
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				SetX(GetX() - speed);
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