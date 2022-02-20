#pragma once
#include "../core/Deleteable.h"
#include <functional>

namespace novazero
{
	namespace core
	{
		class Timer : public Deleteable
		{

		private:

			float m_DelayMax = 1.0f;
			float m_Delay = 0.0f;
			bool m_Loop = false;
			bool m_Alive = true;
			unsigned int m_ID = 0;

			bool m_Randomized = false;
			float m_RandomMin = 0.0f;
			float m_RandomMax = 0.0f;

			bool m_UsingFloatRefs = false;
			float* m_RandomMinRef = nullptr;
			float* m_RandomMaxRef = nullptr;

			std::function<void()> f_OnFinish;

		public:

			Timer(const float delayMS, const bool loop, std::function<void()> endDelayFunc,
				const float loopRndMin = -1.f, const float loopRndMax = -1.f);

			Timer(float* loopRndMin, float* loopRndMax, std::function<void()> endDelayFunc);

			float* GetRefRndMin() { return &m_RandomMin; } // for tweens and Director ref-ing
			float* GetRefRndMax() { return &m_RandomMax; } // for tweens and Director ref-ing

			void DestroySelf();
			
			void Tick();
		};
	}
}