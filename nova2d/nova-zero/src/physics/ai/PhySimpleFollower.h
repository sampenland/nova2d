#pragma once
#include "../../ai/SimpleFollower.h"
#include "../../physics/PhySprite.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace novazero::ai;

			class PhySimpleFollower :
				public SimpleFollower
			{

			private:

			public:

				PhySimpleFollower(Positional* target, float moveDelay);

				void Update();

				void DestroySelf();
			};
		}

	}
}