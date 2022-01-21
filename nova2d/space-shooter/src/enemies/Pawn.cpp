#include "Pawn.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;

	Pawn::Pawn(std::string assetName, Vec2Int position, Vec2Int size, char layer, Positional* target, const float moveUpdateDelay)
		: SimpleFollower(target, moveUpdateDelay)
	{
		AddSprite(assetName, position, size, layer);
		ConfigureCollider(m_Sprite, 0, "pawn");

		m_HealthBar = new SimpleStatBar(false, m_Sprite->GetX(), m_Sprite->GetY() - 2,
			16, 4, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");

		n2dAddUpdater(Pawn::Update, this);
	}

	Pawn::~Pawn()
	{
		if (m_Sprite)
			delete m_Sprite;

		if (m_HealthBar)
			delete m_HealthBar;
	}

	void Pawn::Update()
	{
		if (!m_Alive) return;

		m_HealthBar->Update(m_Health, m_Sprite->GetX(), m_Sprite->GetY() - 8);

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
			if (m_HealthBar)
				delete m_HealthBar;

			DestroySelf();
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
		m_DelayShoot = randomf(m_DelayShootMin, m_DelayShootMax);

		SimpleBulletController* bullet = new 
			SimpleBulletController(
				Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 8), 
				Vec2Int(m_Sprite->GetX(), Game::s_Height + 32), 
				2.0f);

		bullet->AddSprite("pawn-bullet", Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 32), Vec2Int(16, 16), 0);
		bullet->ConfigureCollider(bullet->GetSprite(), 0, "pawn-bullet");
		bullet->Configure(3, Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));

	}
}