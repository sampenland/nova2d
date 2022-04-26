#include "MiniAlien.h"
#include "core/Game.h"
#include "Human.h"
#include "physics/ai/PhySimpleWeakAI.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	MiniAlien::MiniAlien(Vec2 position, float moveDelay) 
		: PhySimpleFollower(nullptr, moveDelay)
	{
		AddPhySprite("mini-alien", position, Vec2(32, 32), 2, Vec2Int(32, 32), "mini-alien");
		GetPhySprite()->ConfigurePhysicsCircle(false, 20);

		Configure(2, 1000.f);

		m_ReTargeter = new Timer(1000, true, n2dMakeFunc(MiniAlien::ReTarget, this), 5000, 10000);
		m_Shooter = new Timer(1000, true, n2dMakeFunc(MiniAlien::Shoot, this), 2500, 5000);

	}

	void MiniAlien::Shoot()
	{
		if (!PhySimpleFollower::GetTarget())
			return;

		LOGS(GetPhySprite()->GetCenterWorldPosition());
		PhySimpleWeakAI* bullet = new PhySimpleWeakAI("mini-alien-bullet", GetPhySprite()->GetCenterWorldPosition(),
			Vec2(16, 16), 2, Vec2Int(16, 16), "mini-alien-bullet");
		bullet->ConfigureRotation(true, 0);
		Vec2 targetPos = PhySimpleFollower::GetTarget()->GetPosition();
		bullet->AddPatrolPointWithFunction(targetPos, bullet->GetLinearPatrolMove());
		bullet->ConfigureOnPatrolComplete([=]() {
			bullet->DestroySelf();
		});

	}

	void MiniAlien::ReTarget()
	{
		if (PhySimpleFollower::GetTarget()) 
			return;

		Human* human = (Human*)n2dReferenceRandomGroupGet("humans");

		if (human)
		{
			PhySimpleFollower::ConfigureTarget((Positional*)human);
		}
		else
		{
			PhySimpleFollower::ConfigureTarget(nullptr);
		}
	}

	void MiniAlien::DestroySelf()
	{
		CleanUpdaters();

		if (m_ReTargeter)
			m_ReTargeter->DestroySelf();
		
		if (m_Shooter)
			m_Shooter->DestroySelf();

		PhySimpleFollower::DestroySelf();
		SetDeleted(true);
	}
}