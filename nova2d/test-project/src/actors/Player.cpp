#include "Player.h"
#include "core/Game.h"
#include "maths/Maths.h"
#include "Rocket.h"

namespace testproject
{
	using namespace novazero::maths;

	Player::Player(const std::string& colliderName, Vec2 position, Vec2 size, unsigned char layer) :
		BasicController(colliderName, colliderName, position,
			Vec2(32, 32), Vec2Int(32, 32), 5)
	{
		m_PlayerName = colliderName;

		ConfigurePhysicsRect(false);
		EnableRotation(false);

		ConfigureMoveSpeed(200);

		auto cid = n2dAddUpdater(Player::Update, this);
		m_CleanUpdaters.push_back(cid);

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i] = new Image("fuel", Vec2(0, 0), Vec2Int(16, 16), 4);
		}

		PhySensor* planet = (PhySensor*)n2dReferenceGet("planet");
		n2dAddCollision(GetPhySprite(), (PhyBase*)planet,
			n2dMakeFunc(Player::StartFueling, this), n2dMakeFunc(Player::StopFueling, this));

		m_Jets = n2dAddParticleSystem("jetfire", Vec2Int(16, 16), colliderName + "-jets", 8, 4, 1);
		m_Jets->SetLifetime(0.25f, 0.7f);

		m_ShootArea = new PhySensor(colliderName + "_shootArea", false, position, 128);
		n2dReferenceAdd(colliderName + "_shootArea", m_ShootArea);
		
	}

	void Player::StartFueling()
	{
		m_Fueling = true;
	}

	void Player::StopFueling()
	{
		m_Fueling = false;
	}

	void Player::ShootArea()
	{
		m_ShootArea->SetBodyPosition(GetPosition() + m_ShootAreaOffset);
	}

	void Player::SetShootKey(SDL_KeyCode key)
	{
		m_ShootKey = key;
	}

	void Player::Shoot()
	{
		if (m_ShootReady > 0.f)
		{
			m_ShootReady--;
			return;
		}

		if (n2dIsKeyDown(m_ShootKey))
		{
			m_ShootReady = SHOOT_RESET;
			MiniAlien* closest = nullptr;

			float min = 99999;
			for (auto alien : m_MiniAliens)
			{
				float distance = Vec2::Distance(GetPosition(), alien->GetPosition());
				if (distance < min)
				{
					closest = alien;
				}
			}

			if (closest != nullptr)
			{
				Rocket* rocket = new Rocket(m_PlayerName, GetPosition(), closest, 1);
			}
		}
	}

	void Player::FuelManage()
	{
		if (GetMoving())
		{
			m_FuelTank -= FUEL_COST;
		}

		if (m_FuelTank < 0)
		{
			if (m_Fuel > 0)
			{
				m_Fuel--;
				m_FuelTank = 100.f;
			}
		}

		if (m_Fuel < 1)
		{
			EnableMove(false);
		}

		if (m_Fueling)
		{
			if (m_FuelTank < 100.f)
			{
				m_FuelTank += (2 * FUEL_COST);
			}
			else
			{
				if (m_Fuel < 5)
				{
					EnableMove(true);
					m_Fuel++;
					m_FuelTank = 0.f;
				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i]->SetPosition(Vec2(GetX() + GetWidth() + 10, GetY() + 28 - (i * 10)));
			if (i < m_Fuel)
			{
				m_FuelDisplay[i]->SetVisible(true);
			}
			else
			{
				m_FuelDisplay[i]->SetVisible(false);
			}
		}
	}

	void Player::Update()
	{
		BasicController::Update();
		FuelManage();

		Jets();
		ShootArea();
		Shoot();
	}

	void Player::Jets()
	{
		if (GetPhySprite())
		{
			if (GetPhySprite()->GetBody())
			{
				if (GetMoving())
				{
					b2Vec2 linearVel = GetPhySprite()->GetBody()->GetLinearVelocity();
					float degrees = Vec2::AngleFromVec2(Vec2(linearVel.x, linearVel.y));
					
					Vec2 unitVec = Vec2::UnitVec2FromAngle(degrees);
					unitVec.multiply(Vec2(128, 128));					
					m_ShootAreaOffset = unitVec;

					Vec2 jetPos = GetPhySprite()->GetCenterWorldPosition();
					m_Jets->BurstParticles(1, Vec2(jetPos.x - 8, jetPos.y - 8) , 10);
				}
			}
		}
	}

	void Player::MiniAlienEnter(PhyBase* a, PhyBase* b)
	{
		PhySensor* sensorA = (PhySensor*)a;
		MiniAlien* mini = (MiniAlien*)sensorA->GetUserData();
		m_MiniAliens.push_back(mini);
	}

	void Player::MiniAlienExit(PhyBase* a, PhyBase* b)
	{
		PhySensor* sensorA = (PhySensor*)a;
		MiniAlien* mini = (MiniAlien*)sensorA->GetUserData();

		std::vector<MiniAlien*>::iterator f = std::find(m_MiniAliens.begin(), m_MiniAliens.end(), mini);
		if (f != m_MiniAliens.end())
		{
			m_MiniAliens.erase(f);
		}

	}

	void Player::DestroySelf()
	{
		CleanUpdaters();
		BasicController::DestroySelf();
	}
}