#include "Pawn.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;

	Pawn::Pawn(std::string assetName, Vec2Int position, Vec2Int size, char layer, Positional* target, const float moveUpdateDelay)
		: SimpleFollower(target, moveUpdateDelay)
	{
		AddSprite(assetName, position, size, layer);
		ConfigureCollider(m_Sprite, 0, "pawn");
		ConfigureUsingBounds(false, false);

		m_HealthBar = new SimpleStatBar(false, m_Sprite->GetX(), m_Sprite->GetY() - 2,
			16, 4, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");

		auto cleanID = n2dAddUpdater(Pawn::Update, this);
		m_CleanUpdaters.push_back(cleanID);
	}

	Pawn::~Pawn()
	{
		if (m_Sprite)
			m_Sprite->DestroySelf();

		if (m_HealthBar)
			m_HealthBar->DestroySelf();
	}

	void Pawn::Update()
	{
		if (!m_Alive) return;

		m_HealthBar->Update(m_Health/2, m_Sprite->GetX(), m_Sprite->GetY() - 8);

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
			Text* t = (Text*)n2dReferenceGet("score");
			auto score = n2dScoreAdd(10);
			t->UpdateText("Score: " + std::to_string(score));

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