#include "Alien.h"
#include "core/Game.h"
#include "core/Timer.h"
#include "../actors/Player.h"
#include "physics/ai/PhySimpleFollower.h"

namespace testproject
{
	using namespace novazero::core;

	Alien::Alien(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		: PhySimpleWeakAI(assetName, position, size, layer)
	{
		
		GetPhysicsSprite()->ConfigurePhysicsRect("alien", false);
		GetPhysicsSprite()->SetScale(2);

		m_Shooter = new Timer(12000.f, true, n2dMakeFunc(Alien::Shoot, this));
		Shoot();

		m_Mover = new Timer(10000.f, true, n2dMakeFunc(Alien::TryMove, this));
		TryMove();

		ClearPatrol();
		
		Configure(10, false);
		EnableAI(true);
	}

	void Alien::TryMove()
	{
		float x = n2dRandomFloat(32, Game::s_Width - 32);
		float y = n2dRandomFloat(32, Game::s_Height - 32);

		ClearPatrol();
		AddPatrolPointWithFunction(Vec2(x, y), GetLinearPatrolMove());

	}

	void Alien::Shoot()
	{
		Player* p = (Player*)n2dReferenceGet("player");
		PhySimpleFollower* bullet = new PhySimpleFollower(p, 10);
		bullet->AddSprite("bullet", GetPosition(), Vec2Int(16, 16), 4);
		Timer* t = new Timer(n2dRandomFloat(2000, 6000), false, [=]() {
			bullet->DestroySelf();
		});
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