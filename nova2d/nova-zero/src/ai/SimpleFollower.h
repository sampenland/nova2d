#pragma once
#include "../core/Game.h"

#include "../core/EventListener.h"
#include "../maths/Rect.h"
#include "../core/BoundUser.h"
#include "../core/TimerWatcher.h"
#include "../physics/Collider.h"
#include "../physics/TimeEffected.h"

namespace novazero
{
	namespace ai
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;
		using namespace physics;

		class SimpleFollower : 
			public EventListener,
			public BoundUser,
			public TimerWatcher,
			public Collider,
			public TimeEffected
		{

		private:

			Positional* m_Target;
			Vec2Int m_TargetOffset;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;
			int m_LookAtDegAdd = 0;
			float m_WaitDelay = 0;
			Vec2Int m_WaitTarget;
			bool m_LookAtTarget = false;
			
		protected:
			Sprite* m_Sprite = nullptr;
			float m_MoveSpeed = 0;

		public:

			SimpleFollower(Positional* target, const float moveUpdateDelayMS);

			void AddSprite(std::string assetName, Vec2 position, Vec2Int size, char layer);
			Sprite* GetSprite() { return m_Sprite; }

			void Configure(float moveSpeed, float delayStart = 0.0f, Vec2Int waitTargetPos = Vec2Int(0,0));
			void ConfigureTarget(Positional* target);
			void ConfigureRotation(bool lookAtTarget, int addToLookAtDeg) { m_LookAtTarget = lookAtTarget; m_LookAtDegAdd = addToLookAtDeg; }
			void Offset(Vec2Int offset) { m_TargetOffset = offset; }
			
			void UpdateFollower();

			void DestroySelf() override;
			void OnCollision(Collision* collision) override;

		};
	}
}