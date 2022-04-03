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

			std::vector<Human*> m_Humans;

		public:

			HumanController();

			void CreateHuman(int count);
		};
	}
}