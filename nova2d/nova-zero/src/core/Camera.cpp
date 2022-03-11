#include "Camera.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Camera::Camera(Vec2 startPos, Rect bounds)
		{
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

		}
	}
}