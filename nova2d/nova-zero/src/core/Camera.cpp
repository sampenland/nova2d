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
				SetMoveBounds(Rect(0, 0, Game::s_Width, Game::s_Height));
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

			if(!Game::s_Director->IsEnabled())
				FollowTarget();
		}

		void Camera::FollowTarget()
		{
			if (!m_FollowTarget) return;

			// Get positions
			Vec2 targetPos = m_FollowTarget->GetPosition();
			Vec2 camSetPos = Vec2(-(targetPos.x - Game::s_Width / 2), -(targetPos.y - Game::s_Height / 2));

			// Keep within camera bounds (or screen space)


			// Position camera
			SetPosition(camSetPos);
			EnforceBounds();

		}

		void Camera::EnforceBounds()
		{
			Rect bounds = GetMoveBounds();
			Vec2 pos = GetPosition();

			if (-pos.x < bounds.x)
			{
				float newX = pos.x - (Game::s_Width/2*CAMERA_ZOOM) - bounds.x;// +(pos.x * 1 / CAMERA_ZOOM);
				//SetX(newX);
			}
			//if (-pos.x > bounds.x + bounds.w) SetX(pos.x > bounds.x + bounds.w);

			//if (pos.y < bounds.y) SetY(bounds.y);
			//if (pos.y > bounds.y + bounds.h) SetY(pos.y > bounds.y + bounds.h);
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

			if (n2dIsKeyDown(SDLK_EQUALS))
			{
				m_Zoom += m_ZoomSpeed;
				m_Scale += m_ZoomSpeed;
			}

			if (n2dIsKeyDown(SDLK_MINUS))
			{
				m_Zoom -= m_ZoomSpeed;
				m_Scale -= m_ZoomSpeed;
				if (m_Zoom < 0)m_Zoom = 0.00001f;
			}

			if (n2dIsKeyDown(SDLK_0))
			{
				m_Scale = 1.f;
				m_Zoom = 1.f;
				SetPosition(Vec2(0, 0));
			}
		}

		void Camera::SetFollowTarget(Positional* target, float zoomLevel, float distanceBeforeFollow, 
			TweenTypes followType) 
		{
			m_FollowTarget = target; 
			SetZoom(zoomLevel);
			SetFollowDistance(distanceBeforeFollow);
			SetFollowType(followType);
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

		// -------------------------
		// Positioning
		Vec2Int Camera::GetPositionInt() const { return Vec2Int((int)m_Position.x, (int)m_Position.y); }
		Vec2 Camera::GetPosition() const { return Vec2((float)m_Position.x, (float)m_Position.y); }

		void Camera::SetX(float x)
		{
			m_Position.x = (int)x;
		}

		void Camera::SetY(float y)
		{
			m_Position.y = (int)y;
		}

		void Camera::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Camera::SetPositionInt(Vec2Int position)
		{
			m_Position = position;
		}
		//-----------------------------------------------
		void Camera::DestroySelf()
		{
			n2dRemoveUpdater(m_CleanID);
		}
	}
}