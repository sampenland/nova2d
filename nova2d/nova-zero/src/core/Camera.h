#pragma once
#include "Positional.h"
#include "BoundUser.h"
#include "../maths/Rect.h"

namespace novazero
{
	namespace core
	{
		class Camera : public Positional, public BoundUser
		{

		private:

			unsigned int m_CleanID = 0;
			unsigned int m_ID = 0;

			float m_Zoom = 1.f;
			float m_ZoomSpeed = 0.001f;
			float m_Scale = 1.f;
			Positional* m_FollowTarget = nullptr;

			bool m_FreeMove = false;
			void FreeMove();

		public:

			Camera(Rect bounds = Rect(0, 0, 0, 0));

			void SetFollowTarget(Positional* target) { m_FollowTarget = target; }

			void MoveX(float deltaX);
			void MoveY(float deltaY);

			void Update();
<<<<<<< Updated upstream
=======
			void FollowTarget();

			void EnforceBounds(Vec2 setPos);
>>>>>>> Stashed changes

			void EnableFreeWASDMove(bool enabled);
			bool IsFreeMoveEnabled() const;

			float GetScale() const;
			void SetScale(float scale);

			float GetZoom() const;
			void SetZoom(float zoomLevel);

<<<<<<< Updated upstream
=======
			Vec2 GetPosition() const;
			Vec2Int GetPositionInt() const;

			void SetX(float x);
			void SetY(float y);

			float GetX() const;
			float GetY() const;

			int OffsetX() { return m_Offset.x; }
			int OffsetY() { return m_Offset.y; }

			void SetOffsetX(int offsetX) { m_Offset.x = offsetX; }
			void SetOffsetY(int offsetY) { m_Offset.y = offsetY; }

			void SetPosition(Vec2 position);
			void SetPositionInt(Vec2Int position);

>>>>>>> Stashed changes
			void DestroySelf() override;

		};
	}
}