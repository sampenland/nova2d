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

			float m_Zoom = 1.f;
			float m_ZoomSpeed = 0.001f;
			float m_Scale = 1.f;
			float m_FollowDistance = 100.f;
			TweenTypes m_FollowType = TweenTypes::EaseInCubic;

			Positional* m_FollowTarget = nullptr;

			bool m_FreeMove = false;
			void FreeMove();

		public:

			Camera(Vec2 startPosition = Vec2(0.f, 0.f), Rect bounds = Rect(0, 0, 0, 0));

			void SetFollowTarget(Positional* target, float zoomLevel = 1.f, 
				float distanceBeforeFollow = 100.f,
				TweenTypes followType = TweenTypes::EaseInCubic);

			void MoveX(float deltaX);
			void MoveY(float deltaY);

			void SetFollowDistance(float dist)
			{
				m_FollowDistance = dist;
			}

			void SetFollowType(TweenTypes type)
			{
				m_FollowType = type;
			}

			void Update();
			void FollowTarget();

			void EnforceBounds();

			void EnableFreeWASDMove(bool enabled) { m_FreeMove = enabled; }
			bool IsFreeMoveEnabled() const { return m_FreeMove; }

			float GetScale() const { return m_Scale; }
			void SetScale(float scale) { m_Scale = scale; m_Zoom = scale; }

			float GetZoom() const { return m_Zoom; }
			void SetZoom(float zoomLevel) { m_Zoom = zoomLevel; m_Scale = zoomLevel; }

			Vec2 GetPosition() const;
			Vec2Int GetPositionInt() const;

			void SetX(float x);
			void SetY(float y);

			float GetX() const { return (float)m_Position.x; }
			float GetY() const { return (float)m_Position.y; }

			int OffsetX() { return m_Offset.x; }
			int OffsetY() { return m_Offset.y; }

			void SetOffsetX(int offsetX) { m_Offset.x = offsetX; }
			void SetOffsetY(int offsetY) { m_Offset.y = offsetY; }

			void SetPosition(Vec2 position);
			void SetPositionInt(Vec2Int position);

			void DestroySelf() override;

		};
	}
}