#pragma once
#include <functional>

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			class TimelineInstance
			{

			protected:

				TimelineInstance() {};

			public:

				void ExecuteNovaEvent(std::function<void()> func)
				{
					func();
				}

			};
		}		
	}
}