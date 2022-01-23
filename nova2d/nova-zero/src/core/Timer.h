#pragma once
#include "TypeDefs.h"
#include "../core/Deleteable.h"

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

			f_VoidFunction f_OnFinish;

		public:

			Timer(const float delayMS, const bool loop, f_VoidFunction endDelayFunc);
			~Timer();

			void DestroySelf();
			
			void Tick();
		};
	}
}