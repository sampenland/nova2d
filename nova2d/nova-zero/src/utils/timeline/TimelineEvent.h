#pragma once
#include <functional>
#include <vector>
#include "../../core/Deleteable.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			class TimelineEvent : public Deleteable
			{

			private:

				float m_TimeTillNextEventSeconds = 0.f; // in seconds
				std::function<bool()> f_NextEventTrigger = nullptr;

				unsigned int m_ID = 0;

			public:
				
				TimelineEvent(float timeTillNextEventSeconds, std::function<bool()> nextEventTrigger);

				// runs when the event begins
				virtual void Start() = 0;

				// returns true when needing to move to next event
				bool Tick();

				// runs when the event ends (optional)
				virtual void End() {};

				virtual void DestroySelf() = 0;

			};
		}
	}
}