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

			unsigned int m_Resources = 0;

		public:

			ResourceController();

			void CreateResource();
		};
	}
}