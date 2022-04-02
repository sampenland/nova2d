#include "Timer.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Timer::Timer(const float delayMS, const bool loop, std::function<void()> endDelayFunc, 
			const float loopRndMin, const float loopRndMax)
			: Deleteable("timer")
		{
			m_DelayMax = delayMS * 2;
			m_Delay = m_DelayMax;
			m_Loop = loop;

			if (loopRndMin != -1.f && loopRndMax != -1.f)
			{
				m_Randomized = true;
				m_RandomMin = loopRndMin;
				m_RandomMax = loopRndMax;
			}

			f_OnFinish = endDelayFunc;

			auto cleanID = n2dAddUpdater(Timer::Tick, this);
			m_DeleteName = "timer_" + std::to_string(cleanID);

			m_CleanUpdaters.push_back(cleanID);

		}

		Timer::Timer(float* loopRndMin, float* loopRndMax, std::function<void()> endDelayFunc)
			: Deleteable("timer")
		{
			m_DelayMax = *loopRndMin * 2;
			m_Delay = m_DelayMax;
			m_Loop = true;

			m_Randomized = true;

			m_UsingFloatRefs = true;
			m_RandomMinRef = loopRndMin;
			m_RandomMaxRef = loopRndMax;

			f_OnFinish = endDelayFunc;

			auto cleanID = n2dAddUpdater(Timer::Tick, this);
			m_DeleteName = "timer_" + std::to_string(cleanID);

			m_CleanUpdaters.push_back(cleanID);

		}

		void Timer::DestroySelf()
		{
 			CleanUpdaters();
			m_Alive = false;

			if (f_OnFinish)
				f_OnFinish = NULL;

			SetDeleted(true);
		}

		void Timer::ResetAndEnable(float delayMS)
		{
			m_Delay = delayMS;
			SetEnabled(true);
		}

		void Timer::Tick()
		{
			if (!IsEnabled()) return;
			if (!m_Alive) return;

			if (m_Delay < 0)
			{
				if(f_OnFinish)
					f_OnFinish();

				if (m_Loop)
				{
					m_Alive = true;

					if (m_Randomized)
					{
						if (m_UsingFloatRefs)
						{
							m_Delay = n2dRandomFloat(*m_RandomMinRef, *m_RandomMaxRef);
						}
						else
						{
							m_Delay = n2dRandomFloat(m_RandomMin, m_RandomMax);
						}
					}
					else
					{
						m_Delay = m_DelayMax;
					}
				}
				else
				{
					DestroySelf();
				}
			}
			else
			{
				m_Delay = (float)(m_Delay - Game::s_DeltaTime);
			}
		}
	}
}