#pragma once

#include "../maths/Rect.h"
#include "../core/Game.h"
#include "../core/BoundUser.h"
#include "../core/TimerWatcher.h"
#include "../physics/Collider.h"

namespace novazero
{
	namespace ai
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;
		using namespace physics;

		class SimpleFollower
			: public EventListener,
			public BoundUser,
			public TimerWatcher,
			public Collider
		{

		private:

			Positional* m_Target;
			Vec2Int m_TargetOffset;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;
			int m_LookAtDegAdd = 0;

			bool m_LookAtTarget = false;
			
		protected:
			Sprite* m_Sprite = nullptr;
			int m_MoveSpeed = 0;

		public:

			SimpleFollower(Positional* target, const float moveUpdateDelay);
			~SimpleFollower();

			void AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			Sprite* GetSprite() { return m_Sprite; }

			void Configure(int moveSpeed);
			void ConfigureTarget(Positional* target);
			void ConfigureRotation(bool lookAtTarget, int addToLookAtDeg) { m_LookAtTarget = lookAtTarget; m_LookAtDegAdd = addToLookAtDeg; }
			void Offset(Vec2Int offset) { m_TargetOffset = offset; }
			
			void Update();

			void DestroySelf() override;
			void OnCollision(const Collision* collision) override;

		};
	}
}