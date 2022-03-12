#include "Camera.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Camera::Camera(Rect bounds)
		{
			m_ID = n2dGameGetID();

			SetPosition(Vec2(0, 0));

			if (bounds.x == 0 && bounds.y == 0 && bounds.w == 0 && bounds.h == 0)
			{
				ConfigureMoveBounds(Rect(0, 0, Game::s_Width, Game::s_Height));
			}
			else
			{
				ConfigureMoveBounds(bounds);
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

			camSetPos.x = targetPos.x;
			camSetPos.y = targetPos.y;

			// Position camera
			EnforceBounds(camSetPos);

		}

		void Camera::EnforceBounds(Vec2 setPos)
		{
			Rect bounds = GetMoveBounds();
			bounds.x = bounds.x - Game::s_Width / 2;

			int newX = -1 * (setPos.x - (Game::s_Width / 2));
			int newY = -1 * (setPos.y - (Game::s_Height / 2));

			newX += m_FollowDistance;
			newY -= m_FollowDistance;
			
			// limit X
			if (newX < bounds.x) newX = bounds.x;
			int xLimit = bounds.x + bounds.w;
			if (newX > xLimit) newX = xLimit;
			
			// limit Y
			int yLimit = (bounds.y + bounds.h) / 2;
			if (newY > bounds.y + yLimit) newY = bounds.y + yLimit;
			if (newY < -yLimit) newY = -yLimit;

			SetPositionInt(Vec2Int(newX, newY));

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
				m_Position.y += speed;
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				m_Position.y -= speed;
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				m_Position.x += speed;
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				m_Position.x -= speed;
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

		void Camera::EnableFreeWASDMove(bool enabled) { m_FreeMove = enabled; }
		bool Camera::IsFreeMoveEnabled() const { return m_FreeMove; }

		float Camera::GetScale() const { return m_Scale; }
		void Camera::SetScale(float scale) { m_Scale = scale; m_Zoom = scale; }

		float Camera::GetZoom() const { return m_Zoom; }
		void Camera::SetZoom(float zoomLevel, bool reposition)
		{
			m_Zoom = zoomLevel;
			m_Scale = zoomLevel;
			
			if (!reposition) return;

			SetX(m_Position.x);
			SetY(m_Position.y);
		}

		// -------------------------
		// Positioning
		// -------------------------
		Vec2Int Camera::GetPositionInt() const 
		{ 
			return Vec2Int((int)GetX(), (int)GetY());
		}
		
		Vec2 Camera::GetPosition() const 
		{ 
			return Vec2(GetX(), GetY()); 
		}

		Vec2 Camera::GetPositionRAW() const
		{
			return Vec2((float)m_Position.x, (float)m_Position.y);
		}

		Vec2Int Camera::GetPositionRAWInt() const
		{
			return m_Position;
		}

		void Camera::SetX(float x)
		{
			m_Position.x = (int)x + (m_Zoom * Game::s_Width / 2);
		}

		void Camera::SetY(float y)
		{
			m_Position.y = (int)y - (m_Zoom * Game::s_Height / 2);
		}

		float Camera::GetX() const 
		{ 
			return (float)m_Position.x - (m_Zoom * Game::s_Width / 2);
		}

		float Camera::GetY() const 
		{ 
			return (float)m_Position.y + (m_Zoom * Game::s_Height / 2);
		}

		void Camera::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Camera::SetPositionInt(Vec2Int position)
		{
			SetX(position.x);
			SetY(position.y);
		}
		//-----------------------------------------------

		void Camera::DestroySelf()
		{
			n2dRemoveUpdater(m_CleanID);
		}
	}
}