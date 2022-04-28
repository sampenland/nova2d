#include "MiniAlien.h"
#include "core/Game.h"
#include "Human.h"
#include "physics/ai/PhySimpleWeakAI.h"
#include "Player.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	MiniAlien::MiniAlien(Positional* target, Vec2 position, float moveDelay) 
		: PhySimpleFollower(target, moveDelay)
	{
		AddSprite("mini-alien", position, Vec2Int(32, 32), 2);
		GetSprite()->AddAnimation("drive", 0, 4, 10, true, nullptr);
		AddPhySensor("mini-alien", false, position, 24, "mini-aliens");

		GetPhySensor()->SetUserData((void*)this);

		float wait = n2dRandomFloat(100.f, 10000.f);
		Configure(2, wait);

		m_ReTargeter = new Timer(1000, true, n2dMakeFunc(MiniAlien::ReTarget, this), 5000, 10000);
		m_Shooter = new Timer(1000, true, n2dMakeFunc(MiniAlien::Shoot, this), 2500, 5000);

		std::string id = tostring(Positional::m_ID);
		m_Jets = n2dAddParticleSystem("jetfire", Vec2Int(16, 16), "jets_" + id, 6, 4, 1);
		m_Jets->SetLifetime(0.32f, 0.5f);

		auto cleanID = n2dAddUpdater(MiniAlien::UpdateMiniAlien, this);
		m_CleanUpdaters.push_back(cleanID);

		PhySensor* player1ShootArea = (PhySensor*)n2dReferenceGet("player1_shootArea");
		PhySensor* player2ShootArea = (PhySensor*)n2dReferenceGet("player2_shootArea");
		
		Player* player1 = (Player*)n2dReferenceGet("player1");
		Player* player2 = (Player*)n2dReferenceGet("player2");

		n2dAddCollision(m_Sensor, player1ShootArea,
			n2dMakeFuncArgs2(Player::MiniAlienEnter, player1, m_Sensor, player1ShootArea),
			n2dMakeFuncArgs2(Player::MiniAlienExit, player1, m_Sensor, player1ShootArea)
		);

		n2dAddCollision(m_Sensor, player1ShootArea,
			n2dMakeFuncArgs2(Player::MiniAlienEnter, player2, m_Sensor, player2ShootArea),
			n2dMakeFuncArgs2(Player::MiniAlienExit, player2, m_Sensor, player2ShootArea)
		);

	}

	void MiniAlien::HitByRocket()
	{
		LOGS("HIT");
	}

	void MiniAlien::UpdateMiniAlien()
	{
		float degrees = GetMoveAngleDegrees();
		Vec2 jetPos = GetSprite()->GetCenterWorldPosition();
		m_Jets->BurstParticles(1, Vec2(jetPos.x - 8, jetPos.y + 6), 10, degrees - 90, degrees + 90);
	}

	void MiniAlien::Shoot()
	{
		if (!PhySimpleFollower::GetTarget())
			return;

		PhySimpleWeakAI* bullet = new PhySimpleWeakAI("mini-alien-bullet", GetSprite()->GetCenterWorldPosition(),
			Vec2(16, 16), 2, Vec2Int(16, 16), "mini-alien-bullet");
		bullet->LookAt(PhySimpleFollower::GetTarget()->GetPositionInt(), 90);
		
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