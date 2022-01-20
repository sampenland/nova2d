#include "Pawn.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;

	Pawn::Pawn(std::string assetName, Vec2Int position, Vec2Int size, char layer, Positional* target, const float moveUpdateDelay)
		: SimpleFollower(target, moveUpdateDelay)
	{
		AddSprite(assetName, position, size, layer);

		n2dAddUpdater(Pawn::Update, this);
	}

	Pawn::~Pawn()
	{
		if (m_Sprite)
			delete m_Sprite;
	}

	void Pawn::Update()
	{
		if (m_DelayShoot < 0)
		{
			Shoot();
			return;
		}

		m_DelayShoot = (float)(m_DelayShoot - Game::s_DeltaTime);
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