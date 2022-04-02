#include "TimelineEvent.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			TimelineEvent::TimelineEvent(TimelineInstance* instanceController, std::function<bool()> nextEventTrigger, float timeTillNextEventSeconds)
				: Deleteable("timelineEvent_")
			{
				m_ID = n2dGameGetID();
				m_DeleteName = "timelineEvent_" + tostring(m_ID);

				m_InstanceController = instanceController;
				m_TimeTillNextEventSeconds = timeTillNextEventSeconds * 1000.f;
				f_NextEventTrigger = nextEventTrigger;

				m_CleanID = n2dAddDeleteable(this);
			}

			bool TimelineEvent::Tick()
			{
				if (!m_Running) return false;

				if (f_NextEventTrigger && f_NextEventTrigger())
				{
					return true; // tell timeline to go to next event
				}

				if (m_TimeTillNextEventSeconds == -1000)
				{
					return false;
				}
				else if (m_TimeTillNextEventSeconds > 0)
				{
					m_TimeTillNextEventSeconds -= n2dDeltaTime * 100;
					return false; // stay on this event
				}
				else
				{
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