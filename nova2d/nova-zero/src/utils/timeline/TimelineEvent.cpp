#include "TimelineEvent.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			TimelineEvent::TimelineEvent(float timeTillNextEventSeconds, std::function<bool()> nextEventTrigger)
				: Deleteable("timelineEvent_")
			{
				m_ID = n2dGameGetID();
				m_DeleteName = "timelineEvent_" + tostring(m_ID);

				m_TimeTillNextEventSeconds = timeTillNextEventSeconds;
				f_NextEventTrigger = nextEventTrigger;

				m_CleanID = n2dAddDeleteable(this);
			}

			bool TimelineEvent::Tick()
			{
				if (!m_Started) return;

				if (f_NextEventTrigger)
				{
					End();
					return true; // tell timeline to go to next event
				}

				if (m_TimeTillNextEventSeconds > 0)
				{
					m_TimeTillNextEventSeconds -= n2dDeltaTime;
					return false; // stay on this event
				}
				else
				{
					End();
					return true;
				}
			}

			void TimelineEvent::DestroySelf()
			{
				CleanUpdaters();
				n2dRemoveDeleteable(m_CleanID);
				SetDeleted(true);
			}
		}
	}
}