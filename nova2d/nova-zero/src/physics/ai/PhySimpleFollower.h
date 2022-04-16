#pragma once
#include "../../ai/SimpleFollower.h"

namespace novazero
{
	namespace physics
	{
		using namespace ai;

		class PhySimpleFollower :
			public SimpleFollower
		{

		private:

		public:

			PhySimpleFollower(Positional* target, float moveDelay);

			void DestroySelf();
		};
	}
}