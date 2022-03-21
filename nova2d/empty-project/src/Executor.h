#pragma once
#include "utils/timeline/TimelineInstance.h"
#include "logging/logging.h"

namespace emptyproject
{
	using namespace novazero::utils::timeline;

	class Executor : public TimelineInstance
	{

	private:

	public:

		void PrintNumber(int num)
		{
			LOGS(num);
		}

	};
}