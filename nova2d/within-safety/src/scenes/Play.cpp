#include "Play.h"
#include "ai/SimpleDirectional.h"

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
		n2dAssetsLoadAndAddTexture("enemy1", "res/enemy1.png");

		m_Planet = new PhySensor("planet", true, Game::GetCenterScreen(), 60);
		m_Player = new PhySprite("player", Game::GetCenterScreen().add(Vec2(0, -200)), Vec2(32,32),
			10, Vec2Int(32,32), "player");
		m_Player->ConfigurePhysicsCircle(false, 20);
		m_Player->DisableAutoRotation();

		m_Enemy1Creator = new Timer(2000.f, true, n2dMakeFunc(Play::CreateEnemy1, this));

		Sprite* s = new Sprite("bullet", m_Planet->GetWorldCenterPosition(), Vec2Int(32, 32), 30);
	}

	void Play::CreateEnemy1()
	{
		Vec2 createAt = Vec2(0, 0);

		int rnd = n2dRandomInt(0, 3);
		float pad = 0.05f;
		switch (rnd)
		{
		case 0:
			// TOP
			createAt = Vec2(n2dRandomFloat(0, Game::s_Width), n2dRandomFloat(0, pad * Game::s_Height));
			break;

		case 1:
			// BOTTOM
			createAt = Vec2(n2dRandomFloat(0, Game::s_Width), n2dRandomFloat(0, (1- pad) * Game::s_Height));
			break;

		case 2:
			// LEFT
			createAt = Vec2(n2dRandomFloat(0, pad * Game::s_Width), n2dRandomFloat(0, Game::s_Height));
			break;

		default:
			// RIGHT
			createAt = Vec2(n2dRandomFloat(0, (1 - pad) * Game::s_Width), n2dRandomFloat(0, Game::s_Height));
			break;
		}

		SimpleDirectional* enemy1 = new SimpleDirectional(m_Planet->GetWorldCenterPosition(), 20.f, 5, "enemy1", createAt,
			Vec2Int(32, 32), 10, "enemy1");
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

			float angle = Vec2::LookAtAngle(m_Player->GetPosition(), m_Planet->GetPosition());
			Vec2 dir = Vec2::UnitVec2FromAngle(angle);
			SimpleDirectional* bullet = new SimpleDirectional(dir, 15, 1.f, "bullet", m_Player->GetPosition(),
				Vec2Int(16, 16), 10, "bullet");
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

		unitVec = Vec2::LookAtVec(m_Player->GetPosition(), m_Planet->GetPosition(), true);
		mag = 200.f * PHYSICS_MULTIPLIER;
		force = b2Vec2(mag * unitVec.x, mag * unitVec.y);
		m_Player->GetBody()->ApplyForce(force, m_Player->GetBody()->GetWorldCenter(), true);

		angle = Vec2::LookAtAngle(m_Planet->GetWorldCenterPosition(), m_Player->GetWorldCenterPosition());
		m_Player->GetSprite()->SetAngle(angle);
	}

}