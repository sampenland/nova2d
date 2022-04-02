#pragma once
#include "ai/SimpleWeakAI.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace novazero::ai;

		class Tree
			: public SimpleWeakAI
		{

		private:

			int m_Row = 0;
			unsigned int m_GridPos = 0;

		public:

			Tree(int row);

			void StartWait();
			void DestroySelf() override;

			void Update();

		};
	}
}