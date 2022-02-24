#include "Timeline.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			Timeline::Timeline() : Deleteable("timeline_")
			{
				m_ID = n2dGameGetID();
				m_DeleteName = "timeline_" + tostring(m_ID);

				m_CleanID = n2dAddDeleteable(this);
			};

			void Timeline::Update()
			{
				if (m_TimelineEvents.size() > m_CurrentEvent)
				{
					// Tick current Timeline Event
					if (m_TimelineEvents[m_CurrentEvent]->Tick())
					{
						if (m_TimelineEvents.size() > m_CurrentEvent + 1)
						{
							m_TimelineEvents[m_CurrentEvent]->SetRunning(false);
							m_CurrentEvent++;
							m_TimelineEvents[m_CurrentEvent]->SetRunning(true);
						}						
					}
				}
			}

			void Timeline::ResetToStartEvent()
			{
				m_CurrentEvent = 0;
			}

			void Timeline::SetEvent(int index)
			{
				if (index >= 0 && index < m_TimelineEvents.size())
				{
					m_CurrentEvent = index;
				}
			}

			void Timeline::DestroySelf()
			{
				for (size_t i = 0; i < m_TimelineEvents.size(); i++)
				{
					m_TimelineEvents[i]->End();
					m_TimelineEvents[i]->DestroySelf();
				}

				m_TimelineEvents.clear();
				n2dRemoveDeleteable(m_CleanID);

				CleanUpdaters();

				SetDeleted(true);
				
			}
		}
	}
}