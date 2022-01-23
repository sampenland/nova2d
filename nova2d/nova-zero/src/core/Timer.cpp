#include "Timer.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Timer::Timer(const float delayMS, const bool loop, std::function<void()> endDelayFunc)
			: Deleteable("timer")
		{
			m_DelayMax = delayMS;
			m_Delay = m_DelayMax;
			m_Loop = loop;

			f_OnFinish = endDelayFunc;

			auto cleanID = n2dAddUpdater(Timer::Tick, this);
			m_DeleteName = "timer_" + std::to_string(cleanID);

			m_CleanUpdaters.push_back(cleanID);

		}

		Timer::~Timer()
		{
			
		}

		void Timer::DestroySelf()
		{
 			CleanUpdaters();
			m_Alive = false;

			if (f_OnFinish)
				f_OnFinish = NULL;

			m_DeleteNow = 1;
		}

		void Timer::Tick()
		{
			if (!m_Alive) return;

			if (m_Delay < 0)
			{
				if(f_OnFinish)
					f_OnFinish();

				if (m_Loop)
				{
					m_Alive = true;
					m_Delay = m_DelayMax;
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