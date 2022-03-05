#pragma once
#include <functional>
#include <vector>
#include "../../core/Deleteable.h"
#include "TimelineInstance.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			using namespace core;

			enum class FuncType
			{
				Void,
				Int1Float1,
				Int2Float1,
				Float2Int1,
				Float2Int2,
				Float,
				Float2,
				Int,
				Int2
			};

			class TimelineEvent : public Deleteable
			{

			private:

				float m_TimeTillNextEventSeconds = -1.f; // in seconds
				std::function<bool()> f_NextEventTrigger = nullptr;

				unsigned int m_ID = 0;
				unsigned int m_CleanID = 0;
				bool m_Running = false;

			public:
				
				TimelineEvent(TimelineInstance* instanceController, std::function<bool()> nextEventTrigger, float timeTillNextEventSeconds = -1.f);

				TimelineInstance* m_InstanceController = nullptr;
				
				// runs when the event begins
				virtual void Execute() = 0;
				void SetRunning(bool val) { m_Running = val; }

				// returns true when needing to move to next event
				bool Tick();

				void DestroySelf();

			};
		}
	}
}