#include "MiniAlien.h"
#include "core/Game.h"
#include "Human.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	MiniAlien::MiniAlien(Vec2 position, Positional* target, float moveDelay) 
		: PhySimpleFollower(target, moveDelay)
	{
		AddPhySprite("mini-alien", position, Vec2(32, 32), 2, Vec2Int(32, 32), "mini-alien");
		GetPhySprite()->ConfigurePhysicsCircle(false, 20);

		PhySimpleFollower::ConfigureTarget(nullptr);

		Human* human = (Human*)n2dReferenceRandomGroupGet("humans");

		if (human)
		{
			PhySimpleFollower::ConfigureTarget(human);
		}

	}

	void MiniAlien::DestroySelf()
	{
		CleanUpdaters();
		PhySimpleFollower::DestroySelf();
		SetDeleted(true);
	}
}