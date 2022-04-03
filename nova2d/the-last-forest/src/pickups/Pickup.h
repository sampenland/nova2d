#pragma once
#include "ai/SimpleWeakAI.h"
#include "components/SimpleStatBar.h"
#include "core/Timer.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace novazero::components;
		using namespace novazero::core;

		class Pickup
		{
		
		public:

			SimpleStatBar* m_DelayDisplay = nullptr;
			Timer* m_DelayTimer = nullptr;
			float m_DelayTime = 5000.f;

		public:

			Pickup(float delayTime);
			
			void Update(Vec2 position);
			void SetVisible(bool isVisible);

			void DestroySelf();

		};
	}
}