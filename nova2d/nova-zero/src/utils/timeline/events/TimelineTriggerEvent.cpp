#include "TimelineTriggerEvent.h"
#include "../../../core/Game.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			namespace events
			{
				using namespace graphics;
				using namespace maths;
				using namespace logging;
				using namespace core;

				// Bool condition trigger for on/off
					// Trigger events cannot be stacked on a timeline (MUST have their own timelines)
				TimelineTrggerEvent::TimelineTrggerEvent(TimelineInstance* instance, std::string nameOfTrigger,
					std::function<void()> onFunc,
					std::function<void()> offFunc,
					std::function<bool()> conditionToWatch,
					float timeBetweenOnOff)
					: TimelineEvent(instance, nullptr, -1.f)
				{
					m_Name = nameOfTrigger;
					m_Triggered = false;
					m_TimeBetweenTriggerAndEndFunc = timeBetweenOnOff;
					m_CurrentTime = 0.f;

					f_ConditionToWatch = conditionToWatch;
					f_OnFunc = onFunc;
					f_OnOffFunc = offFunc;

					m_CleanUpdaters.push_back(n2dAddUpdater(TimelineTrggerEvent::Tick, this));
				}

				void TimelineTrggerEvent::Tick()
				{
					if (!f_OnFunc || !f_OnOffFunc)
					{
						if (n2dDebugVerbose)
						{
							LOG(LVL_NON_FATAL_ERROR, "Trigger event has nullptr ON/OFF function");
						}
						return;
					}

					if (!f_ConditionToWatch)
					{
						if (n2dDebugVerbose)
						{
							LOG(LVL_NON_FATAL_ERROR, "Trigger event has nullptr conditional function");
						}
						return;
					}

					// Using bool func for triggers
					if (m_Triggered)
					{
						if (!f_ConditionToWatch() && m_CurrentTime <= 0.f)
						{
							Trigger(false);
						}
						else if (m_CurrentTime > 0.f)
						{
							m_CurrentTime -= n2dDeltaTime;
						}
					}
					else
					{
						if (f_ConditionToWatch() && m_CurrentTime <= 0.f)
						{
							Trigger(true);
						}
						else if (m_CurrentTime > 0.f)
						{
							m_CurrentTime -= n2dDeltaTime;
						}
					}
				}

				void TimelineTrggerEvent::Trigger(bool isTriggered)
				{
					if (!f_OnFunc || !f_OnOffFunc)
					{
						if (n2dDebugVerbose)
						{
							LOG(LVL_NON_FATAL_ERROR, "Trigger event has nullptr ON/OFF function");
						}
						return;
					}

					m_Triggered = isTriggered;
					m_CurrentTime = m_TimeBetweenTriggerAndEndFunc;

					if (m_Triggered)
					{
						f_OnFunc();
					}
					else
					{
						f_OnOffFunc();
					}

				}
			}
		}
	}
}