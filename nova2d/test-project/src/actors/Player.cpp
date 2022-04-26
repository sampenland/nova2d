#include "Player.h"
#include "core/Game.h"
#include "maths/Maths.h"

namespace testproject
{
	using namespace novazero::maths;

	Player::Player(const std::string& colliderName, Vec2 position, Vec2 size, unsigned char layer) :
		BasicController(colliderName, colliderName, position,
			Vec2(32, 32), Vec2Int(32, 32), 5)
	{

		ConfigurePhysicsRect(false);
		EnableRotation(false);

		auto cid = n2dAddUpdater(Player::Update, this);
		m_CleanUpdaters.push_back(cid);

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i] = new Image("fuel", Vec2(0, 0), Vec2Int(16, 16), 4);
		}

		PhySensor* planet = (PhySensor*)n2dReferenceGet("planet");
		n2dAddCollision(GetPhySprite(), (PhyBase*)planet,
			n2dMakeFunc(Player::StartFueling, this), n2dMakeFunc(Player::StopFueling, this));

		m_Jets = n2dAddParticleSystem("jetfire", Vec2Int(16, 16), colliderName + "-jets", 100, 4, 1);
		m_Jets->SetLifetime(0.5f, 1.2f);
		
	}

	void Player::StartFueling()
	{
		m_Fueling = true;
	}

	void Player::StopFueling()
	{
		m_Fueling = false;
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
	}

	void Player::Jets()
	{
		if (GetPhySprite())
		{
			if (GetPhySprite()->GetBody())
			{
				if (GetMoving())
				{
					float radians = GetPhySprite()->GetBody()->GetAngle() + PI;
					float degrees = n2dRadToDeg(radians);
					Vec2 jetPos = GetPhySprite()->GetCenterWorldPosition();
					m_Jets->BurstParticles(1, Vec2(jetPos.x - 8, jetPos.y - 8) , 10, degrees - 30, degrees + 30);
				}
			}
		}
	}

	void Player::DestroySelf()
	{
		CleanUpdaters();
		BasicController::DestroySelf();
	}
}