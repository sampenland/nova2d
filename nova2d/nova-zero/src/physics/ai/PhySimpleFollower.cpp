#include "PhySimpleFollower.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			PhySimpleFollower::PhySimpleFollower(Positional* target, float moveDelay) :
				SimpleFollower(target, moveDelay)
			{
				if (!target)
				{
					LOG(LVL_W, "PhySimpleFollower has no target", __FILE__, __LINE__);
				}

				auto cid = n2dAddUpdater(PhySimpleFollower::Update, this);
				m_CleanUpdaters.push_back(cid);

			}

			void PhySimpleFollower::Update()
			{
				
			}

			void PhySimpleFollower::DestroySelf()
			{
				CleanUpdaters();
				SimpleFollower::DestroySelf();
			}
		}
	}
}