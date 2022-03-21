#include "TimelinesExample.h"
#include "core/Game.h"
#include "utils/timeline/events/TimelineExecuteEvent.h"
#include "utils/timeline/events/TimelineTriggerEvent.h"

namespace emptyproject
{

	using namespace novazero::core;
	using namespace novazero::utils::timeline::events;

	TimelinesExample::TimelinesExample(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void TimelinesExample::Start()
	{
		// Simple title
		m_Title = new Text("font1", "Timelines Example", "white",
			Rect(200, 100, 300, 50), 0);

		// This timer just shows that the conditional function below is required before
		// the timeline will progress
		Timer* t = new Timer(2000, false, n2dMakeFunc(TimelinesExample::SetLowHealth, this));

		// Conditional timeline events
		TimelineExecuteEvent* conditional = new TimelineExecuteEvent(nullptr,
			n2dMakeFunc(TimelinesExample::PlayerHealthLow, this), -1);

		n2dAddTimeline("timeline_name", conditional);

		// ------------------------------------------------

		// Timed function call timeline event
		// 
		// Calls a function in a different class
		// 
		// Wait 2 seconds then print '100'
		TimelineExecuteEvent* printAnum = new TimelineExecuteEvent(m_Executor,
			nullptr, 2000);
		std::function<void(int)> func = n2dMakeFuncArgs1(Executor::PrintNumber, m_Executor);
		printAnum->SetFunction(func, (int)100);

		n2dAddTimeline("timeline_name", printAnum);



		// -----------------------------------------------

		// Trigger timeline events

		// Another little timer to control the player health. These timers are
		// just to show what's happening. The conditional function below (watchHealth)
		// when added to a timeline is checked each frame and when it returns true,
		// the function calls are processed based on how you setup your timeline.
		auto setLowerHealth = new auto ([=]() {
			m_PlayerHealth = 9;
		});
		Timer* t2 = new Timer(3000, false, *setLowerHealth);

		// Using a lambda function to make timeline example
		// remain simple
		// 
		// this is just a function on the heap that watches the players 
		// health
		auto watchHealth = new auto ([=]() -> bool {
			return m_PlayerHealth < 10;
		});

		// The below event works like this:
		/*
		
		if the conditional function (watchHealth) goes true (gets triggered),
		then the onTrigger function (TriggeredOn) gets called. There is then
		a 'cool down' or wait before another trigger can happen (below that is set
		to 1000 (1 second)). Once the cool down has finished, the conditional
		function begins to be watched again and will start the process over when
		triggered.

		v.0.0.5 trigger event syntax:
		TimelineTrggerEvent::TimelineTrggerEvent(TimelineInstance* instance, std::string nameOfTrigger,
					std::function<void()> onFunc,
					std::function<void()> offFunc,
					std::function<bool()> conditionToWatch,
					float timeBetweenOnOff)


		The below will never run TriggeredOff because the *watchHealth function is always
		returning true after we set it with the timer.

		*/
		TimelineTrggerEvent* triggerEvent = new TimelineTrggerEvent(nullptr, 
			"call-for-help", n2dMakeFunc(TimelinesExample::TriggeredOn, this), 
			n2dMakeFunc(TimelinesExample::TriggeredOff, this),
			*watchHealth, 1000);

		n2dAddTimeline("timeline_name", triggerEvent);

		// IMPORTANT - you must activate/start the timeline like so:
		n2dStartTimeline("timeline_name");

	}

	void TimelinesExample::SetLowHealth()
	{
		if (m_Title)
			m_Title->UpdateText("Player has low health!");

		m_PlayerHealth = 19;
	}

	bool TimelinesExample::PlayerHealthLow()
	{
		return m_PlayerHealth < 20;
	}

	void TimelinesExample::TriggeredOn()
	{
		if (m_Title)
			m_Title->UpdateText("TRIGGERED!");
	}

	void TimelinesExample::TriggeredOff()
	{
		if (m_Title)
			m_Title->UpdateText("NOT TRIGGERED!");
	}

	void TimelinesExample::Update()
	{

	}

	void TimelinesExample::End()
	{

	}

	void TimelinesExample::DestroySelf()
	{
		m_Title->DestroySelf();
	}
}