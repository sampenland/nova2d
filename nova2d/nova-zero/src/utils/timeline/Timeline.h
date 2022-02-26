#pragma once
#include <vector>
#include "TimelineEvent.h"
#include "../../core/Deleteable.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			class Timeline : public Deleteable
			{

			private:

				int m_CurrentEvent = 0;
				unsigned int m_ID = 0;
				unsigned int m_CleanID = 0;

				std::string m_TimelineName = "";

				std::vector<TimelineEvent*> m_TimelineEvents;

			public:

				Timeline(const std::string& timelineName);

				void Update();

				void ResetToStartEvent(bool running);

				void AddEvent(TimelineEvent* timelineEvent);
				void SetEvent(int index);

				void DestroySelf();

			};
		}
	}
}