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

			m_DrawArea = Rect(0, 0, Game::s_Width, Game::s_Height);
			ConfigureUsingBounds(true, false);

			m_CleanID = n2dAddUpdaterPersistent(Camera::Update, this);

		}

		void Camera::Update()
		{
			if (m_Zoom != m_OldZoom)
			{
				m_OldZoom = m_Zoom;
				m_DrawArea.w = Game::s_Width * m_Zoom;
				m_DrawArea.h = Game::s_Height * m_Zoom;
			}

			m_DrawArea.x = GetX();
			m_DrawArea.y = GetY();

			// -----------

			if (m_FreeMove)
				FreeMove();

			if (!Game::s_Director->IsEnabled())
			{				
				FollowTarget();
			}
		}

		void Camera::FollowTarget()
		{
			if (!m_FollowTarget) return;

			// Get positions
			Vec2 targetPos = m_FollowTarget->GetPosition();
			Vec2 camSetPos = Vec2(-(targetPos.x - Game::s_Width / 2), -(targetPos.y - Game::s_Height / 2));

			camSetPos.x = targetPos.x * CAMERA_ZOOM;
			camSetPos.y = targetPos.y * CAMERA_ZOOM;

			// Position camera
			EnforceBounds(camSetPos);

		}

		void Camera::EnforceBounds(Vec2 setPos)
		{
			Rect bounds = GetMoveBounds();
			bounds.x = bounds.x - Game::s_Width / 2;

			float newX = -1 * (setPos.x - (Game::s_Width / 2));
			float newY = -1 * (setPos.y - (Game::s_Height / 2));

			if (m_FollowTarget->IsFacing() == Directions::Right)
			{
				newX += m_FollowDistance;
			}
			else if(m_FollowTarget->IsFacing() == Directions::Left)
			{
				newX += (Game::s_Width / 2 / CAMERA_ZOOM) + m_FollowDistance;
			}

			if (m_FollowTarget->IsFacing() == Directions::Down)
			{
				newY += m_FollowDistance;
			}
			else if (m_FollowTarget->IsFacing() == Directions::Up)
			{
				newY += (Game::s_Height / 2 / CAMERA_ZOOM) + m_FollowDistance;
			}
			
			// limit X
			if (newX < bounds.x) newX = bounds.x;
			int xLimit = bounds.x + bounds.w;
			if (newX > xLimit) newX = xLimit;
			
			// limit Y
			int yLimit = (bounds.y + bounds.h) / 2;
			if (newY > bounds.y + yLimit) newY = bounds.y + yLimit;
			if (newY < -yLimit) newY = -yLimit;

			// prep for camera move (tween to new spot)
			float correction = (m_Zoom * Game::s_Height / 2);
			newX = newX + correction;
			newY = newY + correction;

			SetPosition(Vec2(newX, newY));

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

			if (n2dIsKeyDown(SDLK_1))
			{
				m_Zoom = 1.f;
				m_Scale = 1.f;
			}

			if (n2dIsKeyDown(SDLK_2))
			{
				m_Zoom = 2.f;
				m_Scale = 2.f;
			}

			if (n2dIsKeyDown(SDLK_3))
			{
				m_Zoom = 3.f;
				m_Scale = 3.f;
			}

			if (n2dIsKeyDown(SDLK_4))
			{
				SetPosition(Vec2(100, 100));
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

		void Camera::SetFollowTarget(Positional* target, float followSpeed, bool startOnTargetPosition, float zoomLevel, float distanceBeforeFollow, 
			TweenTypes followType) 
		{
			m_FollowTarget = target; 
			SetZoom(zoomLevel);
			SetFollowDistance(distanceBeforeFollow);
			SetFollowType(followType);
			SetFollowSpeed(followSpeed);

			if (startOnTargetPosition)
			{
				//SetPosition(target->GetCenter());
			}
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

		// Positioning
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
			m_Position.x = -x;
		}

		void Camera::SetY(float y)
		{
			m_Position.y = -y;
		}

		void Camera::CenterOn(Positional* target)
		{
			SetPosition(Vec2(
				target->GetCenter().x + (m_Zoom * Game::s_Width/2), 
				target->GetCenter().y - (m_Zoom * Game::s_Height/2)
			));
		}

		void Camera::CenterOn(Vec2 position)
		{
			SetPosition(Vec2(
				position.x + (m_Zoom * Game::s_Width / 2),
				position.y - (m_Zoom * Game::s_Height / 2)
			));
		}

		float Camera::GetX() const 
		{ 
			return (float)m_Position.x;
		}

		float Camera::GetY() const 
		{ 
			return (float)m_Position.y;
		}

		void Camera::SetPosition(Vec2 position)
		{
			SetX(position.x);
			SetY(position.y);
		}

		void Camera::SetPosition(Positional* target)
		{
			SetX(target->GetX());
			SetY(target->GetY());
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