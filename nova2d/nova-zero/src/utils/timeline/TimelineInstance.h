#pragma once
#include <functional>

namespace novazero
{
	namespace core
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