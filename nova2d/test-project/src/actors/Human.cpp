#include "Human.h"
#include "physics/PhySensor.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::physics;

	Human::Human(Vec2 position, int skill)
		: PhySimpleWeakAI("human", position, Vec2(32, 32), 2, Vec2Int(32, 32), "human"), m_Skill(skill)
	{
		GetPhySprite()->ConfigurePhysicsCircle(false, 20);
		
		m_MoveTimer = new Timer(2000.f, true, n2dMakeFunc(Human::Move, this), 5000, 10000);
		Move();

		PhySensor* planet = (PhySensor*)n2dReferenceGet("planet");
		n2dAddCollision(GetPhysicsSprite(), (PhyBase*)planet, n2dMakeFunc(Human::AtPlanet, this), nullptr);

		EnableAI(true);
		Configure(555, false);

		n2dReferenceGroupAdd("human_" + m_ID, this, "humans");

	}

	void Human::AtPlanet()
	{
		m_MoveTimer->SetEnabled(false);
		m_MoveTimer->DestroySelf();
		
		Timer* t = new Timer(2000.f, false, n2dMakeFunc(Human::DestroySelf, this));
	}

	void Human::Move()
	{
		static int headToPlanet = 0;
		headToPlanet++;

		if (headToPlanet >= m_Skill)
		{
			headToPlanet = 0;
			ClearPatrol();
			AddPatrolPointWithFunction(Vec2(Game::s_Width - 32, Game::s_Height - 32), GetLinearPatrolMove());
		}
		else
		{
			ClearPatrol();
			Vec2 nextPos = Vec2::Random(Vec2(0, 0), Vec2(Game::s_Width, Game::s_Height));
			AddPatrolPointWithFunction(nextPos, GetLinearPatrolMove());
		}
	}

	void Human::DestroySelf()
	{
		CleanUpdaters();
		PhySimpleWeakAI::DestroySelf();
		SetDeleted(true);
	}
}