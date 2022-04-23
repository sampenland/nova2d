#include "Player.h"
#include "core/Game.h"
#include "maths/Maths.h"

namespace testproject
{
	using namespace novazero::maths;

	Player::Player(const std::string& colliderName, Vec2 position, Vec2 size, unsigned char layer) :
		BasicController("player", colliderName, position,
			Vec2(32, 32), Vec2Int(128, 128), 5)
	{

		ConfigurePhysicsRect(false);
		EnableRotation(false);
		
		if (GetPhySprite())
		{
			GetPhySprite()->AddAnimation("up", 0, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("right", 2, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("left", 4, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("down", 6, 2, 1, true, nullptr);

			GetPhySprite()->SetOrigin(-42, -46);
		}

		auto cid = n2dAddUpdater(Player::Update, this);
		m_CleanUpdaters.push_back(cid);

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i] = new Image("fuel", Vec2(0, 0), Vec2Int(16, 16), 4);
		}

		PhySensor* planet = (PhySensor*)n2dReferenceGet("planet");
		n2dAddCollision(GetPhySprite(), (PhyBase*)planet,
			n2dMakeFunc(Player::StartFueling, this), n2dMakeFunc(Player::StopFueling, this));
		
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
			m_Fuel--;
			m_FuelTank = 100.f;
		}

		if (m_Fuel < 1)
		{
			EnableMove(false);
			StopAnimation();
			JumpToFrame(1);
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
					m_Fuel++;
					m_FuelTank = 0.f;
				}
			}
		}

		for (int i = 4; i > 0; i--)
		{
			m_FuelDisplay[i]->SetPosition(Vec2(GetX() + GetWidth() + 10, GetY() + -16 + (i * 10)));
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

		Animations();
	}

	void Player::Animations()
	{
		if (GetPhySprite())
		{
			if (GetPhySprite()->GetBody())
			{
				if (!GetMoving())
				{
					StopAnimation();
					JumpToFrame(1);
				}
				else
				{
					Directions dir = GetDirection();
					switch (dir)
					{
					case Directions::Up:
						ChangeAnimation("up");
						StartAnimation();
						break;
					case Directions::Down:
						ChangeAnimation("down");
						StartAnimation();
						break;
					case Directions::Right:
						ChangeAnimation("right");
						StartAnimation();
						break;
					case Directions::Left:
						ChangeAnimation("left");
						StartAnimation();
						break;
					default:
						StopAnimation();
						JumpToFrame(1);
						break;
					}
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