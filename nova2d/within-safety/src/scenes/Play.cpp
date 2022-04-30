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

		n2dAssetsLoadAndAddTexture("player", "res/player.png");
		n2dAssetsLoadAndAddTexture("bullet", "res/bullet.png");

		m_Planet = new PhySensor("planet", true, Game::GetCenterScreen(), 60);
		m_Player = new PhySprite("player", Game::GetCenterScreen().add(Vec2(0, -200)), Vec2(32,32),
			10, Vec2Int(32,32), "player");
		m_Player->ConfigurePhysicsCircle(false, 20);
		m_Player->DisableAutoRotation();
	}
	
	void Play::End()
	{

	}

	void Play::Update()
	{
		ForceControl();
		ShootControl();
	}

	void Play::ShootControl()
	{
		if (m_ShootReady > 0)
		{
			m_ShootReady--;
			return;
		}

		if (n2dIsKeyDown(SDLK_SPACE))
		{
			m_ShootReady = SHOOT_RESET;

			float angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition(), 180);
			Vec2 dir = Vec2::UnitVec2FromAngle(angle);
			PhySimpleDirectional* bullet = new PhySimpleDirectional(dir, 2000, 2, "bullet",
				m_Player->GetPosition().add(dir.multiply(Vec2(40, 40))), Vec2(12, 12), 10,
				Vec2Int(32, 32), "bullet");
		}
	}

	void Play::ForceControl()
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
		mag = 200.f * PHYSICS_MULTIPLIER;
		force = b2Vec2(mag * unitVec.x, mag * unitVec.y);
		m_Player->GetBody()->ApplyForce(force, m_Player->GetBody()->GetWorldCenter(), true);

		angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition(), -90);
		m_Player->GetSprite()->SetAngle(angle);
	}

}