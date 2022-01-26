#include "Pawn.h"
#include "graphics/Text.h"
#include "Leader.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;
	using namespace novazero::core;

	Pawn::Pawn(std::string assetName, Vec2Int position, Vec2Int size, char layer, const float moveUpdateDelay)
		: SimpleWeakAI()
	{


		m_DeleteName = assetName + std::to_string(m_ID);
		
		AddSprite(assetName, position, size, layer);
		ConfigureCollider(m_Sprite, 0, "pawn");
		ConfigureUsingBounds(false, false);

		m_HealthBar = new SimpleStatBar(false, m_Sprite->GetX(), m_Sprite->GetY() - 2,
			16, 4, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");

		auto cleanID = n2dAddUpdater(Pawn::PawnUpdate, this);
		m_CleanUpdaters.push_back(cleanID);

		n2dAddDeleteable(this);
	}

	Pawn::~Pawn()
	{
		
	}

	void Pawn::PawnUpdate()
	{
		if (!m_Alive) return;

		m_HealthBar->Update(m_Health*2, m_Sprite->GetX(), m_Sprite->GetY() - 8);

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

		SimpleBulletController* bullet = new 
			SimpleBulletController(
				Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 8), 
				Vec2Int(m_Sprite->GetX(), Game::s_Height + 32), 
				2.0f);

		bullet->AddSprite("pawn-bullet", Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 32), Vec2Int(16, 16), 0);
		bullet->ConfigureCollider(bullet->GetSprite(), 0, "pawn-bullet");
		bullet->Configure(3, Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));

	}

	void Pawn::DestroySelf()
	{
		if (m_Destroyed) return;

		m_Alive = false;
		m_Destroyed = true;

		Leader* leader = (Leader*)n2dReferenceGet("leader");
		if (leader)
		{
			leader->m_PawnCount--;
		}

  		if (m_HealthBar)
			m_HealthBar->DestroySelf();

		m_DeleteNow = 1;
		SimpleWeakAI::DestroySelf();
	}
}