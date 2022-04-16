#include "PhySimpleFollower.h"

namespace novazero
{
	namespace physics
	{
		PhySimpleFollower::PhySimpleFollower(Positional* target, float moveDelay) :
			SimpleFollower(target, moveDelay)
		{
			if (!target)
			{
				LOG(LVL_W, "PhySimpleFollower has no target");
			}

		}

		void PhySimpleFollower::DestroySelf()
		{
			CleanUpdaters();
			SimpleFollower::DestroySelf();
		}
	}
}