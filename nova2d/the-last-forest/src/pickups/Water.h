#pragma once
#include "Pickup.h"
#include "ai/SimpleWeakAI.h"
#include "components/SimpleStatBar.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace novazero::ai;
		using namespace novazero::components;

		class Water :
			public Pickup,
			public SimpleWeakAI
		{

		private:

			int m_Row = 0;
			unsigned int m_GridPos = 0;

		public:

			Water(int row);

			void StartWait();
			void DestroySelf() override;

			void Update();

		};
	}
}