#include "Timer.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Timer::Timer(const float delayMS, const bool loop, f_VoidFunction endDelayFunc)
		{
			m_DelayMax = delayMS;
			m_Delay = m_DelayMax;
			m_Loop = loop;

			m_OnFinish = endDelayFunc;

			n2dAddUpdater(Timer::Update, this);
		}

		Timer::~Timer()
		{
			n2dRemoveUpdater(Timer::Update, this);
		}

		void Timer::DestroySelf()
		{
			m_Alive = false;

			n2dRemoveUpdater(Timer::Update, this);
		}

		void Timer::Update()
		{
			if (!m_Alive) return;

			if (m_Delay < 0)
			{
				m_OnFinish();

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