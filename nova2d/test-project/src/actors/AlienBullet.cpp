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
		AddPhySprite("bullet", position, Vec2(16, 16), 4, Vec2Int(16,16), "alien-bullet");
		PhySprite* sprite = GetPhySprite();
		if (sprite)
		{
			GetPhySprite()->ConfigurePhysicsSensorCircle(false, 8);
		}
		else
		{
			LOG(LVL_NFE, "NULL alien bullet sprite");
			return;
		}

		Timer* t = new Timer(n2dRandomFloat(2000, 6000), false, [=]() {
			DestroySelf();
		});

		Player* player = (Player*)n2dReferenceGet("player");
		
		if (!player->GetBody())
		{
			LOGS("No player body");
		}
		else
		{
			m_Collision = n2dAddCollision(GetPhySprite(), player,
				n2dMakeFuncArgs2(AlienBullet::HitPlayer, this, this, player), nullptr);
		}

	}

	void AlienBullet::HitPlayer(PhyBase* self, PhyBase* other)
	{
		if (other->GetColliderName() == "player")
		{
			Player* p = (Player*)n2dReferenceGet("player");
			if (p)
			{
				p->Hurt(30);
				DestroySelf();
			}
		}
	}

	void AlienBullet::DestroySelf()
	{
		n2dRemoveCollision(m_Collision);
		SimpleFollower::DestroySelf();
	}
}