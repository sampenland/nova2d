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
			}
			/*if (m_Zoom != m_OldZoom)
			{
				m_OldZoom = m_Zoom;
				
				m_DrawArea.w = Game::s_Width / m_Zoom;
				m_DrawArea.h = Game::s_Height / m_Zoom;
			}

			m_DrawArea.x = -GetX();
			m_DrawArea.y = GetY();*/

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

			SetPosition(Vec2(newX, newY));

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
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				m_DrawArea.y += speed;
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				m_DrawArea.x -= speed;
			}

			if (n2dIsKeyDown(SDLK_d))
			{
				m_DrawArea.x += speed;
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
			
			LOGS("--------");
			LOGS("ZOOM [ " + tostring(m_Zoom) + " ]");

			// Calculate translation
			Vec2 viewportSize = Vec2(Game::s_Width / m_Zoom, Game::s_Height / m_Zoom);
			Vec2 bottomRight = GetBottomRightWorldPosition();
			Vec2 cameraPosition = GetPosition();

			Vec2 position = Vec2(0, 0);
			position.x = bottomRight.x - (0.5f * viewportSize.x);
			position.y = bottomRight.y - (0.5f * viewportSize.y);

			// Factor for how much to scale zoom
			float multi = std::pow(m_Zoom - 1, 2) + m_Zoom - 1;
			position.multiply(Vec2(multi, multi));
			
			// Translate
			SetDrawRectPosition(position);
			
			std::cout << "DrawRect [ " << m_DrawArea << " ]" << std::endl;
			LOGS("--------");
			
			return;

		}	

		// Positioning
		Vec2 Camera::GetCenterScreenWorldPosition()
		{
			Vec2 btmRight = GetBottomRightWorldPosition();
			return btmRight.divide(Vec2(2, 2));
		}

		Vec2 Camera::GetBottomRightWorldPosition(float zoom)
		{
			if (zoom == -1.f)
				zoom = m_Zoom;

			float x = (Game::s_Width / zoom); // TODO: add back cam position
			float y = (Game::s_Height / zoom);

			//LOGS(tostring(x) + " , " + tostring(y));
			return Vec2(x, y);
		}

		Vec2 Camera::GetWorldPosition()
		{
			float x = -1 * (GetX() - Game::s_Width);
			float y = -1 * (GetY() - Game::s_Height);

			if (m_Zoom != 1.f)
			{
				x = x * (1 / m_Zoom);
				y = y * (1 / m_Zoom);
			}

			return Vec2(x, y);
		}

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
			CenterOn(Vec2(target->GetCenter().x, target->GetCenter().y));
		}

		void Camera::CenterOn(Vec2 position)
		{
			//TODO: check this function
			LOG(LVL_I, "is this centering working?");
			SetX(position.x - (m_Zoom * (Game::s_Width / 2)));
			SetY(position.y - (m_Zoom * (Game::s_Height / 2)));
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

		Vec2 Camera::GetOffset() const
		{
			return m_Offset;
		}

		void Camera::SetOffset(Vec2 offset)
		{
			SetOffsetX(offset.x);
			SetOffsetY(offset.y);
		}

		void Camera::SetPosition(Positional* target)
		{
			SetX(target->GetX());
			SetY(target->GetY());
		}

		void Camera::SetPositionInt(Vec2Int position)
		{
			SetX((float)position.x);
			SetY((float)position.y);
		}
		//-----------------------------------------------

		void Camera::DestroySelf()
		{
			n2dRemoveUpdater(m_CleanID);
		}
	}
}