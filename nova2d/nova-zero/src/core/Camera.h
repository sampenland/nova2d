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
			float m_Scale = 1.f;
			Positional* m_FollowTarget = nullptr;

			bool m_FreeMove = false;

		public:

			Camera(Vec2 startPosition = Vec2(0.f, 0.f), Rect bounds = Rect(0, 0, 0, 0));

			void SetFollowTarget(Positional* target) { m_FollowTarget = target; }

			void MoveX(float deltaX);
			void MoveY(float deltaY);

			void Update();

			void EnableFreeWASDMove(bool enabled) { m_FreeMove = enabled; }
			void FreeMove();

			float GetScale() const { return m_Scale; }
			void SetScale(float scale) { m_Scale = scale; }

			float GetZoom() const { return m_Zoom; }
			void SetZoom(float zoomLevel) { m_Zoom = zoomLevel; }

			void DestroySelf() override;

		};
	}
}