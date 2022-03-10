#pragma once
#include "../TimelineEvent.h"
#include "../../../graphics/Drawable.h"
#include "../../../maths/Rect.h"
#include "../../../logging/logging.h"
#include "../../../core/SceneManager.h"
#include "../TimelineInstance.h"

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

				class TimelineTrggerEvent : public TimelineEvent
				{

				private:

					std::string m_Name = "trigger";

					bool m_Triggered = false;
					
					float m_CurrentTime = 0.f;
					float m_TimeBetweenTriggerAndEndFunc = 0.f;
					std::function<void()> f_OnFunc;
					std::function<void()> f_OnOffFunc;
					std::function<bool()> f_ConditionToWatch;

				public:

					// Bool condition trigger for on/off
					// Trigger events cannot be stacked on a timeline (MUST have their own timelines)
					TimelineTrggerEvent(TimelineInstance* instance, std::string nameOfTrigger,
						std::function<void()> onFunc,
						std::function<void()> offFunc,
						std::function<bool()> conditionToWatch,
						float timeBetweenOnOff = 0.f);

					void Tick();

					void Trigger(bool isTriggered);

					void Execute() override { } // Not used
				};
			}
		}
	}
}