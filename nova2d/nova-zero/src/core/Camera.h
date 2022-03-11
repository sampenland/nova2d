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

			float m_Zoom = 1.f;
			Positional* m_FollowTarget = nullptr;

		public:

			Camera(Vec2 startPosition = Vec2(0.f, 0.f), Rect bounds = Rect(0, 0, 0, 0));

			void SetFollowTarget(Positional* target) { m_FollowTarget = target; }

			void MoveX(float deltaX);
			void MoveY(float deltaY);

			void DestroySelf() override;

		};
	}
}