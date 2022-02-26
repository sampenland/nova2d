#pragma once
#include "../TimelineEvent.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			namespace events
			{
				class TimelineCreateEvent : public TimelineEvent
				{

				private:

					Vec2 m_CreatePosition;

				public:

					TimelineCreateEvent(NovaInstance* instance, Vec2 createPosition,
						std::function<bool()> nextEventTrigger, float timeTillNextEventSeconds = 1.f) : 
						TimelineEvent(instance, nextEventTrigger, timeTillNextEventSeconds)
					{
						m_CreatePosition = createPosition;
					}

					void Execute() override
					{
						m_InstanceController->CreateInstance(m_CreatePosition);
					}
				};
			}
		}
	}
}