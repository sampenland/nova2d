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

			std::vector<Tree*> m_Trees;

		public:

			TreeController();

			void CreateTree(int count);
		};
	}
}