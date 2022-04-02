#pragma once
#include "ai/SimpleWeakAI.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::ai;
		using namespace novazero::physics;

		class Human : 
			public SimpleWeakAI
		{

		private:


		public:

			Human(Vec2 position, Vec2Int size, unsigned char layer);

			void OnCollision(Collision* collision);
 
		};
	}
}