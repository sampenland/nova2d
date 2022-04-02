#pragma once
#include "ai/SimpleWeakAI.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace novazero::ai;

		class Water
			: public SimpleWeakAI
		{

		private:

		public:

			Water(int row);

			void StartWait();
			void DestroySelf() override;

		};
	}
}