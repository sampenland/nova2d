#include "Alien.h"
#include "core/Game.h"
#include "core/Timer.h"
#include "../actors/Player.h"
#include "physics/ai/PhySimpleFollower.h"
#include "AlienBullet.h"

namespace testproject
{
	using namespace novazero::core;

	Alien::Alien(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		: PhySimpleWeakAI(assetName, position, Vec2(size.x, size.y), layer, size, "alien")
	{
		SetPosition(position);

		GetPhysicsSprite()->ConfigurePhysicsRect(false);
		GetPhysicsSprite()->SetScale(2);
		GetPhysicsSprite()->EnableRotation(false);

		m_Shooter = new Timer(12000.f, true, n2dMakeFunc(Alien::Shoot, this));
		Shoot();

		m_Mover = new Timer(10000.f, true, n2dMakeFunc(Alien::TryMove, this));
		TryMove();

		ClearPatrol();
		
		Configure(1, false);
		EnableAI(true);
		
	}

	MiniAlien* Alien::CreateMiniAlien(Positional* target, Vec2 position)
	{
		float moveDelay = n2dRandomFloat(10, 50);
		MiniAlien* mini = new MiniAlien(target, position, moveDelay);
		
		mini->ConfigureScatterOffset(Vec2Int(128, 128));
		mini->ConfigureInRange(200);
		m_MiniAliens.push_back(mini);
		return mini;
	}

	void Alien::TryMove()
	{
		float x = n2dRandomFloat(32, Game::s_Width - 32);
		float y = n2dRandomFloat(32, Game::s_Height - 32);

		AddPatrolPointWithFunction(Vec2(x, y), GetLinearPatrolMove());

	}

	void Alien::Shoot()
	{
		return;
		Player* p;

		if (n2dCoinFlip())
		{
			p = (Player*)n2dReferenceGet("player1");
		}
		else
		{
			p = (Player*)n2dReferenceGet("player2");
		}

		AlienBullet* bullet = new AlienBullet(
			GetCenter(), p, 10);
		
	}

	void Alien::DestroySelf()
	{
		if (m_Shooter)
			m_Shooter->DestroySelf();

		if (m_Mover)
			m_Mover->DestroySelf();

		if (GetPhysicsSprite())
			GetPhysicsSprite()->DestroySelf();

		SimpleWeakAI::DestroySelf();

	}
}