#pragma once
#include "utils/timeline/TimelineInstance.h"
#include <vector>
#include "../pickups/Tree.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace novazero::utils::timeline;
		using namespace pickups;

		class TreeController
			: public TimelineInstance
		{

		private:

			unsigned int m_Trees = 0;

		public:

			TreeController();

			void CreateTree();
		};
	}
}