#pragma once
#include "Positional.h"
#include "BoundUser.h"
#include "../maths/Rect.h"
#include "../utils/Tweens.h"

namespace novazero
{
	namespace core
	{
		using namespace utils;

		class Camera : public Positional, public BoundUser
		{

		private:

			unsigned int m_CleanID = 0;
			unsigned int m_ID = 0;

			Rect m_DrawArea = Rect(0, 0, 0, 0);
			float m_Zoom = 1.f;
			float m_OldZoom = 1.f;
			float m_ZoomSpeed = 0.01f;
			float m_FollowDistance = 100.f;

			Positional* m_FollowTarget = nullptr;

			TweenTypes m_FollowType = TweenTypes::EaseInCubic;
			Vec2 m_TweenToPosition = Vec2(0, 0);
			float m_NewX = 0;
			float m_NewY = 0;
			float m_FollowSpeed = 1000.f;

			bool m_FreeMove = false;
			void FreeMove();

		public:

			Camera(Rect bounds = Rect(0, 0, 0, 0));

			void SetFollowTarget(Positional* target, float followSpeed, bool startOnTargetPosition, float zoomLevel, float distanceBeforeFollow,
				TweenTypes followType);

			void SetFollowDistance(float dist)
			{
				m_FollowDistance = dist;
			}

			void SetFollowType(TweenTypes type)
			{
				m_FollowType = type;
			}

			void SetFollowSpeed(float speed)
			{
				m_FollowSpeed = speed;
			}

			void Update();
			void FollowTarget();

			Vec2 GetCenterScreenWorldPosition();

			void CenterOn(Positional* target);
			void CenterOn(Vec2 position);

			void EnforceBounds(Vec2 setPos);

			void EnableFreeWASDMove(bool enabled);
			bool IsFreeMoveEnabled() const;

			Rect GetDrawArea() const;

			float GetZoom() const;
			void SetZoom(float zoomLevel);

			Vec2 GetPosition() const;
			Vec2 GetPositionRAW() const;
			Vec2Int GetPositionRAWInt() const;
			Vec2Int GetPositionInt() const;

			void SetX(float x);
			void SetY(float y);

			float GetX() const;
			float GetY() const;

			int OffsetX() { return m_Offset.x; }
			int OffsetY() { return m_Offset.y; }

			void SetOffsetX(int offsetX) { m_Offset.x = offsetX; }
			void SetOffsetY(int offsetY) { m_Offset.y = offsetY; }

			void SetOffset(Vec2 offset);

			void SetPosition(Vec2 position);
			void SetPosition(Positional* target);
			void SetPositionInt(Vec2Int position);

			void DestroySelf() override;

		};
	}
}