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
				m_DrawArea.w = Game::s_Width / m_Zoom;
				m_DrawArea.h = Game::s_Height / m_Zoom;
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

			Vec2 centerOn = m_FollowTarget->GetCenter();
			Rect bounds = GetMoveBounds();

			if (!(
				centerOn.x - m_DrawArea.w / 2 < bounds.x ||
				centerOn.x + m_DrawArea.w / 2 > bounds.x + bounds.w
				))
			{
				// Within bounds
				centerOn.x = m_FollowTarget->GetCenter().x;				
			}
			else
			{
				if (centerOn.x - m_DrawArea.w / 2 < bounds.x)
				{
					centerOn.x = bounds.x + m_DrawArea.w / 2;
				}
				else if (centerOn.x + m_DrawArea.w / 2 > bounds.x + bounds.w)
				{
					centerOn.x = bounds.x + bounds.w - m_DrawArea.w / 2;
				}
			}

			if (!(
				centerOn.y - m_DrawArea.h / 2 < bounds.y ||
				centerOn.y + m_DrawArea.h / 2 > bounds.y + bounds.h
				))
			{
				// Within bounds
				centerOn.y = m_FollowTarget->GetCenter().y;
			}
			else
			{
				if (centerOn.y - m_DrawArea.h / 2 < bounds.y)
				{
					centerOn.y = bounds.y + m_DrawArea.h / 2;
				}
				else if (centerOn.y + m_DrawArea.h / 2 > bounds.y + bounds.h)
				{
					centerOn.y = bounds.y + bounds.h - m_DrawArea.h / 2;
				}
			}

			CenterOn(centerOn);

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
				m_Offset.y -= speed / m_Zoom;
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				m_DrawArea.y += speed;
				m_Offset.y += speed / m_Zoom;
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				m_DrawArea.x -= speed;
				m_Offset.x -= speed / m_Zoom;
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				m_DrawArea.x += speed;
				m_Offset.x += speed / m_Zoom;
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

		void Camera::SetFollowTarget(Positional* target, float followSpeed, bool startOnTargetPosition, float zoomLevel, 
			float camPadding, TweenTypes followType) 
		{
			if (target == nullptr)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot have camera follow nullptr target.");
				return;
			}

			m_FollowTarget = target;
			SetFollowType(followType);
			SetCameraPadding(camPadding);
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

		Vec2 Camera::GetDrawRectCenter() const
		{
			return Vec2((m_DrawArea.x + m_DrawArea.w / 2) / m_Zoom, (m_DrawArea.y + m_DrawArea.h / 2) / m_Zoom);
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

		void Camera::SetZoom(float zoomLevel, bool force)
		{
			if (m_OldZoom == zoomLevel && !force) return;

			if (zoomLevel == -1.f)
				zoomLevel = m_Zoom;

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

		}	

		Vec2 Camera::GetWorldPosition() const
		{
			return Vec2(m_DrawArea.x, m_DrawArea.y);
		}

		void Camera::CenterOn(Positional* target, float zoom)
		{
			CenterOn(Vec2(target->GetCenter().x, target->GetCenter().y), zoom);
		}

		void Camera::CenterOn(Vec2 position, float zoom)
		{
			// Reposition draw area
			m_Offset.x = position.x - m_DrawArea.w;
			m_Offset.y = position.y - m_DrawArea.h;

			// Apply changes (with force = true)
			SetZoom(zoom, true);
		}

		Vec2 Camera::ReverseCenterOn(Vec2 position)
		{
			return Vec2(position.x - m_DrawArea.w / 2, position.y - m_DrawArea.h / 2);
		}

		Vec2 Camera::GetPosition() const
		{
			return Vec2(GetX(), GetY());
		}

		Vec2Int Camera::GetPositionInt() const
		{
			return Vec2Int((int)GetX(), (int)GetY());
		}

		float Camera::GetX() const
		{
			return m_Offset.x + Game::s_Width - m_DrawArea.w;
		}

		float Camera::GetY() const
		{
			return m_Offset.y + Game::s_Height - m_DrawArea.h;
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