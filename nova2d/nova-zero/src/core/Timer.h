#pragma once
#include "TypeDefs.h"

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

			f_VoidFunction f_OnFinish;

		public:

			Timer(const float delayMS, const bool loop, f_VoidFunction endDelayFunc);
			~Timer();

			void Reset(const float delayMS, bool loop);
			void DestroySelf();
			
			void Update();
		};
	}
}