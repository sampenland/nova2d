#include "Pawn1.h"
#include "../Player.h"
#include "../scenes/Lvl1.h"
#include "components/HitDisplay.h"

namespace spaceshooter
{
	Pawn1::Pawn1(Vec2 position) : SimpleWeakAI()
	{
		AddSprite("pawn1", position, Vec2Int(16, 16), 0);
		m_Sprite->ConfigureAnimation(0, 16, 16, 100, true);
		Configure(10, false);
		ConfigureCollider(m_Sprite, 0, "pawn1");
	}

	void Pawn1::DisplayHit(int damage)
	{
		HitDisplay* hitDisplay = new HitDisplay("+ " + std::to_string(damage), "font4", "yellow", Rect(GetX() - (float)GetWidth() / 2.f, GetY() - 16.f, 24.f, 16.f),
			Vec2(GetX(), GetY() - 128), 4000, 0);
	}

	void Pawn1::Hurt(int damage, const std::string& damager)
	{
		if (m_Alive)
		{
			m_KilledBy = damager;
			n2dScoreAdd(25);
			DisplayHit(25);
			DestroySelf();
		}
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
		pawn1Bullet->ConfigureCollider(pawn1Bullet->GetSprite(), 0, "pawn1-bullet");
		pawn1Bullet->ConfigureTimeEffected(pawn1Bullet->GetSprite());
		pawn1Bullet->Configure(20, false);
		pawn1Bullet->ConfigureContinueAfterPatrolComplete(true);
		pawn1Bullet->AddPatrolPointWithFunction(player->GetPosition(), std::bind(&SimpleWeakAI::LinearPatrolMove, pawn1Bullet));
		pawn1Bullet->ConfigureAliveBounds(Game::GetGameBounds(32));
		pawn1Bullet->LookAt(player->GetPositionInt(), -90);
	}
}