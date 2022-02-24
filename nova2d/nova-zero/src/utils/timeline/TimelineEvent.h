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
				unsigned int m_CleanID = 0;
				bool m_Running = false;

			public:
				
				TimelineEvent(float timeTillNextEventSeconds, std::function<bool()> nextEventTrigger);

				// runs when the event begins
				virtual void Start() = 0;
				void SetRunning(bool val) { m_Running = val; }

				// returns true when needing to move to next event
				bool Tick();

				// runs when the event ends (optional)
				virtual void End() {};

				void DestroySelf();

			};
		}
	}
}