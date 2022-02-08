#include "Pawn1.h"
#include "../Player.h"
#include "../scenes/Lvl1.h"

namespace spaceshooter
{
	Pawn1::Pawn1(Vec2 position) : SimpleWeakAI()
	{
		AddSprite("pawn1", position, Vec2Int(16, 16), 0);
		m_Sprite->ConfigureAnimation(0, 16, 16, 100, true);
		Configure(10, false);
		ConfigureCollider(m_Sprite, 0, "pawn1");
	}

	void Pawn1::Shoot()
	{
		Player* player;
		if (Lvl1::s_Players == 1)
		{
			player = (Player*)n2dReferenceGet("player1");
		}
		else
		{
			if (n2dCoinFlip())
			{
				player = (Player*)n2dReferenceGet("player1");
			}
			else
			{
				player = (Player*)n2dReferenceGet("player2");

			}
		}

		SimpleWeakAI* pawn1Bullet = new SimpleWeakAI();
		pawn1Bullet->EnableAI(true);
		pawn1Bullet->AddSprite("pawn1-bullet", Vec2(GetX(), GetY()), Vec2Int(16, 16), 0);
		pawn1Bullet->ConfigureTimeEffected(pawn1Bullet->GetSprite());
		pawn1Bullet->Configure(20, false);
		pawn1Bullet->ConfigureContinueAfterPatrolComplete(true);
		pawn1Bullet->AddPatrolPointWithFunction(player->GetPosition(), std::bind(&SimpleWeakAI::LinearPatrolMove, pawn1Bullet));
		pawn1Bullet->ConfigureAliveBounds(Game::GetGameBounds(32));
		pawn1Bullet->LookAt(player->GetPositionInt(), -90);
	}
}