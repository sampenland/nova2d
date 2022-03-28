#include "Camera.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Camera::Camera(Rect bounds)
		{
			m_ID = n2dGameGetID();

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
			}

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
			float xLimit = bounds.x + bounds.w;
			if (newX > xLimit) newX = xLimit;
			
			// limit Y
			float yLimit = (bounds.y + bounds.h) / 2;
			if (newY > bounds.y + yLimit) newY = bounds.y + yLimit;
			if (newY < -yLimit) newY = -yLimit;

			// prep for camera move (tween to new spot)
			float correction = (m_Zoom * Game::s_Height / 2);
			newX = newX + correction;
			newY = newY + correction;

		}

		void Camera::FreeMove()
		{
			int speed = 2;

			if (n2dIsKeyDown(SDLK_LSHIFT))
			{
				speed *= 4;
			}

			if (n2dIsKeyDown(SDLK_w))
			{
				m_DrawArea.y -= speed;
				m_Offset.y -= speed;
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				m_DrawArea.y += speed;
				m_Offset.y += speed;
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				m_DrawArea.x -= speed;
				m_Offset.x -= speed;
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				m_DrawArea.x += speed;
				m_Offset.x += speed;
			}

			if (n2dIsKeyDown(SDLK_1))
			{
				SetZoom(1.f);
			}

			if (n2dIsKeyDown(SDLK_2))
			{
				SetZoom(2.f);
			}

			if (n2dIsKeyDown(SDLK_3))
			{
				SetZoom(3.f);
			}

			if (n2dIsKeyDown(SDLK_4))
			{
				SetZoom(4.f);
			}

			if (n2dIsKeyDown(SDLK_5))
			{
				SetZoom(5.f);
			}

			if (n2dIsKeyDown(SDLK_6))
			{
				SetZoom(6.f);
			}

			if (n2dIsKeyDown(SDLK_EQUALS))
			{
				float z = m_Zoom + m_ZoomSpeed;
				SetZoom(z);
			}

			if (n2dIsKeyDown(SDLK_MINUS))
			{
				if (m_Zoom - m_ZoomSpeed > 0.25f)
				{
					float z = m_Zoom - m_ZoomSpeed;
					SetZoom(z);
				}				
			}

			if (n2dIsKeyDown(SDLK_0))
			{
				SetZoom(1.f);
				SetDrawRectPosition(Vec2(0, 0));
				m_Offset = Vec2(0, 0);
			}
		}

		void Camera::SetFollowTarget(Positional* target, float followSpeed, bool startOnTargetPosition, float zoomLevel, float distanceBeforeFollow, 
			TweenTypes followType) 
		{
			m_FollowTarget = target;
			SetFollowDistance(distanceBeforeFollow);
			SetFollowType(followType);
			SetFollowSpeed(followSpeed);

			if (startOnTargetPosition)
			{
				CenterOn(target, zoomLevel);
			}
		}

		void Camera::EnableFreeWASDMove(bool enabled) { m_FreeMove = enabled; }
		bool Camera::IsFreeMoveEnabled() const { return m_FreeMove; }

		void Camera::SetDrawRect(Rect drawRect)
		{
			m_DrawArea = drawRect;
		}

		void Camera::SetDrawRectPosition(Vec2 pos)
		{
			m_DrawArea.x = pos.x;
			m_DrawArea.y = pos.y;
		}

		Rect Camera::GetDrawRect() const
		{
			return m_DrawArea;
		}

		Vec2 Camera::GetDrawRectPosition() const
		{
			return Vec2(m_DrawArea.x, m_DrawArea.y);
		}

		Vec2 Camera::GetDrawRectSize() const
		{
			return Vec2(m_DrawArea.w, m_DrawArea.h);
		}
		
		float Camera::GetZoom() const 
		{ 
			return m_Zoom; 
		}

		void Camera::SetZoom(float zoomLevel)
		{
			if (m_OldZoom == zoomLevel) return;

			// Apply zoom
			m_Zoom = zoomLevel;

			// Calculate translation
			Vec2 zoomCenter = m_Offset;
			Vec2 viewportSize = Vec2(Game::s_Width / m_Zoom, Game::s_Height / m_Zoom);
			
			Vec2 position = Vec2(0, 0);
			position.x = (Game::s_Width / m_Zoom) - (0.5f * viewportSize.x);
			position.y = (Game::s_Height / m_Zoom) - (0.5f * viewportSize.y);

			// Factor for how much to scale zoom
			float multi = (float)std::pow(m_Zoom - 1, 2) + m_Zoom - 1;
			position.multiply(Vec2(multi, multi));

			position.x += zoomCenter.x * m_Zoom;
			position.y += zoomCenter.y * m_Zoom;

			// Translate
			SetDrawRectPosition(position);
			
			return;

		}	

		Vec2 Camera::GetWorldPosition() const
		{
			return Vec2(m_DrawArea.x, m_DrawArea.y);
		}

		void Camera::CenterOn(Positional* target, float zoom)
		{
			if (zoom == -1.f)
				zoom = m_Zoom;

			CenterOn(Vec2(target->GetCenter().x, target->GetCenter().y), zoom);
		}

		void Camera::CenterOn(Vec2 position, float zoom)
		{
			// Reposition draw area
			m_Offset.x = position.x - m_DrawArea.w / 2;
			m_Offset.y = position.y - m_DrawArea.h / 2;

			// Apply changes (with zoom, if required)
			SetZoom(zoom);
		}

		void Camera::Reset()
		{
			m_DrawArea = Rect(0, 0, Game::s_Width, Game::s_Height);
			SetZoom(1.f);
		}

		void Camera::DestroySelf()
		{
			n2dRemoveUpdater(m_CleanID);
		}
	}
}