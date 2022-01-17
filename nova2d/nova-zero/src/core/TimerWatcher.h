#pragma once
#include "Timer.h"
#include <vector>

namespace novazero
{
	namespace core
	{
		class TimerWater 
		{
		protected:
			TimerWater() {};

		private:

			std::vector<Timer*> m_Timers;

		public:

			void AddTimer(Timer* timer)
			{
				m_Timers.push_back(timer);
			}

			void RemoveTimer(Timer* timer)
			{
				std::vector<Timer*>::iterator f = std::find(m_Timers.begin(), m_Timers.end(), timer);
				if (m_Timers.end() != f)
				{
					m_Timers.erase(f);
				}
			}

		};
	}
}