#pragma once
#include "../core/EventListener.h"
#include "../maths/Rect.h"
#include "../core/BoundUser.h"
#include "../core/TimerWatcher.h"
#include "../core/Meta.h"
#include "../physics/PhySprite.h"

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
			public Meta
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
			PhySprite* m_PhySprite = nullptr;
			float m_MoveSpeed = 0;
			bool m_UsingPhySprite = false;

		public:

			SimpleFollower(Positional* target, const float moveUpdateDelayMS);

			void AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);
			void AddPhySprite(const std::string& assetName, Vec2 position, Vec2 size, 
				unsigned char layer, Vec2Int displaySize, const std::string& colliderName);
			Sprite* GetSprite() { return m_Sprite; }
			PhySprite* GetPhySprite() { return m_PhySprite; }

			void Configure(float moveSpeed, float delayStart = 0.0f, Vec2Int waitTargetPos = Vec2Int(0,0));
			void ConfigureTarget(Positional* target);
			void ConfigureRotation(bool lookAtTarget, int addToLookAtDeg) { m_LookAtTarget = lookAtTarget; m_LookAtDegAdd = addToLookAtDeg; }
			void Offset(Vec2Int offset) { m_TargetOffset = offset; }
			
			Positional* GetTarget() const;

			void UpdateFollower();

			void DestroySelf() override;

		};
	}
}