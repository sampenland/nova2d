#pragma once
#include "Game.h"

namespace novazero
{
	namespace core
	{
		class Timer
		{

		private:

			float m_DelayMax = 1.0f;
			float m_Delay = 0.0f;
			bool m_Loop = false;
			bool m_Alive = true;

			f_VoidFunction m_OnFinish;

		public:

			Timer(const float delayMS, const bool loop, f_VoidFunction endDelayFunc)
			{
				m_DelayMax = delayMS / 1000;
				m_Delay = m_DelayMax;

				m_OnFinish = endDelayFunc;

				Game::AddUpdater(std::bind(&Timer::Update, this));
			}

			void Update()
			{
				if (!m_Alive) return;

				if (m_Delay < 0)
				{
					if (m_Loop)
					{
						m_Alive = true;
						m_Delay = m_DelayMax;
					}
					else
					{
						m_Alive = false;
					}

					m_OnFinish();

				}
				else
				{
					m_Delay -= Game::s_DeltaTime;
				}
			}

			~Timer()
			{
				Game::RemoveUpdater(std::bind(&Timer::Update, this));
			}
		};
	}
}