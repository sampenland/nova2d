#include "Timeline.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			Timeline::Timeline(const std::string& name) : Deleteable("timeline_")
			{
				m_ID = n2dGameGetID();
				m_DeleteName = "timeline_" + name + "_" + tostring(m_ID);

				m_CleanID = n2dAddDeleteable(this);
			};

			void Timeline::Update()
			{
				if (m_CurrentEvent == -1) return;

				if (m_TimelineEvents.size() > m_CurrentEvent)
				{
					// Tick current Timeline Event
					if (m_TimelineEvents[m_CurrentEvent]->Tick())
					{
						m_TimelineEvents[m_CurrentEvent]->Execute();

						if (m_TimelineEvents.size() > m_CurrentEvent + 1)
						{
							m_TimelineEvents[m_CurrentEvent]->SetRunning(false);
							m_CurrentEvent++;
							m_TimelineEvents[m_CurrentEvent]->SetRunning(true);
						}
						else
						{
							m_CurrentEvent = -1;
						}
					}
				}
			}

			void Timeline::ResetToStartEvent()
			{
				m_CurrentEvent = 0;
			}

			void Timeline::AddEvent(TimelineEvent* timelineEvent)
			{
				m_TimelineEvents.push_back(timelineEvent);
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