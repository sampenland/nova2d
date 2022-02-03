#include "Pawn.h"
#include "graphics/Text.h"
#include "Leader.h"
#include "../specials/PawnBullet.h"
#include "../Player.h"
#include "../scenes/Lvl1.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;
	using namespace novazero::core;

	Pawn::Pawn(std::string assetName, Vec2 position, Vec2Int size, char layer, const float moveUpdateDelay)
		: SimpleWeakAI()
	{
		Leader::s_PawnCount++;
		
		m_DeleteName = assetName + std::to_string(SimpleWeakAI::Collider::m_ID);
		
		AddSprite(assetName, position, size, layer);
		ConfigureCollider(m_Sprite, 0, "pawn");
		ConfigureUsingBounds(false, false);

		m_HealthBar = new SimpleStatBar(false, (int)m_Sprite->GetX(), (int)m_Sprite->GetY() - 2,
			16, 4, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");

		auto cleanID = n2dAddUpdater(Pawn::PawnUpdate, this);
		m_CleanUpdaters.push_back(cleanID);

		n2dAddDeleteable(this);
	}

	void Pawn::PawnUpdate()
	{
		if (!m_Alive) return;

		m_HealthBar->Update(m_Health*2, (int)m_Sprite->GetX(), (int)m_Sprite->GetY() - 8);

		if (m_DelayShoot < 0)
		{
			Shoot();
			return;
		}

		m_DelayShoot = (float)(m_DelayShoot - Game::s_DeltaTime);
	}

	void Pawn::Hurt(int damage)
	{
		SmallExplosion();

		m_Health -= damage;
		if (m_Health < 1)
		{
			if (m_Alive)
			{
				n2dScoreAdd(14);
				DestroySelf();
			}
		}
		else
		{
			n2dScoreAdd(4);
		}
	}

	void Pawn::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", m_Sprite->GetPosition(), Vec2Int(16, 16), 0);
		explosion->ConfigureAnimation(0, 5, 100, true);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->ConfigureAnimationEnd(*animEnd);
	}

	void Pawn::Shoot()
	{
		auto r = n2dRandomFloat(m_DelayShootMin, m_DelayShootMax);
		m_DelayShoot = r;

		PawnBullet* bullet = new PawnBullet(Vec2Int((int)m_Sprite->GetX(), (int)m_Sprite->GetY() + 8),
			Vec2Int((int)m_Sprite->GetX(), (int)Game::s_Height + 32),
			2.0f, m_Sprite);
	}

	void Pawn::DestroySelf()
	{
		if (m_Destroyed) return;

		if (Lvl1::s_Players == 1)
		{
			Player* player1 = (Player*)n2dReferenceGet("player1");
			player1->NewKill();
		}
		else
		{
			Player* player1 = (Player*)n2dReferenceGet("player1");
			player1->NewKill();
			Player* player2 = (Player*)n2dReferenceGet("player2");
			player2->NewKill();
		}

		m_Alive = false;
		m_Destroyed = true;

		Leader::s_PawnCount--;

  		if (m_HealthBar)
			m_HealthBar->DestroySelf();

		if (m_Sprite)
			m_Sprite->DestroySelf();

		SimpleWeakAI::DestroySelf(); // TODO: possible bug
	}
}