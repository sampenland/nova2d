#pragma once
#include "utils/timeline/TimelineInstance.h"
#include <vector>
#include "../pickups/Sun.h"
#include "../pickups/Water.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace novazero::utils::timeline;
		using namespace pickups;

		class ResourceController
			: public TimelineInstance
		{

		private:

			std::vector<Sun*> m_Suns;
			std::vector<Water*> m_Waters;

		public:

			ResourceController();

			void CreateResource(int count);
		};
	}
}