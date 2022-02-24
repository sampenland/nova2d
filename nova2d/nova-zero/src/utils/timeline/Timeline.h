#pragma once
#include <vector>
#include "TimelineEvent.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			class Timeline
			{

			private:

				int m_CurrentEvent = 0;
				std::vector<TimelineEvent*> m_TimelineEvents;

			public:

				Timeline() {};

				void Update()
				{

					// Tick current event
					if (m_TimelineEvents.size() > m_CurrentEvent)
					{

						

					}

				}

			};
		}
	}
}