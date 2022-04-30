#include "Play.h"

namespace withinsafety
{
	Play::Play(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void Play::Start()
	{
		EnablePhysics(true);
		PhysicsEnableDebug(true);

		n2dAddColor("background", "092925", 255);
		n2dSetBackgroundColor("background");

		m_Planet = new PhySensor("planet", true, Game::GetCenterScreen(), 60);
		m_Player = new PhySprite("player", Game::GetCenterScreen().add(Vec2(0, -200)), Vec2(32,32),
			10, Vec2Int(32,32), "player");
		m_Player->ConfigurePhysicsCircle(false, 20);
	}
	
	void Play::End()
	{

	}

	void Play::Update()
	{
		float angle = 0.f;
		Vec2 unitVec = Vec2(0, 0);
		float mag = 100;
		b2Vec2 force = b2Vec2(0, 0);

		if (n2dIsKeyDown(SDLK_RIGHT))
		{
			angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition(), -70);
			unitVec = Vec2::UnitVec2FromAngle(angle);
			mag = 1000.f * PHYSICS_MULTIPLIER;
			force = b2Vec2(mag * unitVec.x, mag * unitVec.y);
			m_Player->GetBody()->ApplyForce(force, m_Player->GetBody()->GetWorldCenter(), true);
		}

		if (n2dIsKeyDown(SDLK_LEFT))
		{
			angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition(), 70);
			unitVec = Vec2::UnitVec2FromAngle(angle);
			mag = 1000.f * PHYSICS_MULTIPLIER;
			force = b2Vec2(mag * unitVec.x, mag * unitVec.y);
			m_Player->GetBody()->ApplyForce(force, m_Player->GetBody()->GetWorldCenter(), true);
		}

		angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition(), 0);
		unitVec = Vec2::UnitVec2FromAngle(angle);
		mag = 100.f * PHYSICS_MULTIPLIER;
		force = b2Vec2(mag * unitVec.x, mag * unitVec.y);
		m_Player->GetBody()->ApplyForce(force, m_Player->GetBody()->GetWorldCenter(), true);
	}

}