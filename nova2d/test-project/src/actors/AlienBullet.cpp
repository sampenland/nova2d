#include "AlienBullet.h"
#include "core/Timer.h"
#include "core/Game.h"
#include "Player.h"

namespace testproject
{
	using namespace novazero::core;
	using namespace novazero::physics::ai;

	AlienBullet::AlienBullet(Vec2 position, Positional* target, float moveDelay) 
		: PhySimpleFollower(target, moveDelay)
	{
		AddPhySprite("bullet", position, Vec2Int(16, 16), 4, Vec2Int(16,16));
		PhySprite* sprite = GetPhySprite();
		if (sprite)
		{
			GetPhySprite()->ConfigurePhysicsSensorCircle("bullet", false, 8);
		}
		else
		{
			LOG(LVL_NFE, "NULL alien bullet sprite");
			return;
		}

		Timer* t = new Timer(n2dRandomFloat(2000, 6000), false, [=]() {
			DestroySelf();
		});
	}

	void AlienBullet::DestroySelf()
	{
		
		CleanUpdaters();
		SimpleFollower::DestroySelf();
	}
}