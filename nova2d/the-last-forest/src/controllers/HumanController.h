#pragma once
#include "utils/timeline/TimelineInstance.h"
#include <vector>
#include "../actors/Human.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace novazero::utils::timeline;
		using namespace actors;

		class HumanController
			: public TimelineInstance
		{

		private:

			unsigned int m_Humans = 0;

		public:

			HumanController();

			void CreateHuman();
		};
	}
}