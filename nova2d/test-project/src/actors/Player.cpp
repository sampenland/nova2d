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
	}

	void Player::Update()
	{
		BasicController::Update();

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i]->SetPosition(Vec2(GetX() + GetWidth() + 10, GetY() + - 10 + (i * 10)));
			if (i < m_Fuel)
			{
				m_FuelDisplay[i]->SetVisible(true);
			}
			else
			{
				m_FuelDisplay[i]->SetVisible(false);
			}
		}

		Animations();
	}

	void Player::Animations()
	{
		if (GetPhySprite())
		{
			if (GetPhySprite()->GetBody())
			{
				const float thres = 10.f;
				const b2Vec2 velocity = GetPhySprite()->GetBody()->GetLinearVelocity();

				if (std::abs(velocity.x) > std::abs(velocity.y))
				{
					if (velocity.x > thres)
					{
						ChangeAnimation("right");
						StartAnimation();
					}
					else if (velocity.x < -thres)
					{
						ChangeAnimation("left");
						StartAnimation();
					}
					else
					{
						// Stop jets
						StopAnimation();
						GetPhySprite()->JumpToFrame(1);
					}
				}
				else
				{
					if (velocity.y > thres)
					{
						ChangeAnimation("down");
						StartAnimation();
					}
					else if (velocity.y < -thres)
					{
						ChangeAnimation("up");
						StartAnimation();
					}
					else
					{
						// Stop jets
						StopAnimation();
						GetPhySprite()->JumpToFrame(1);
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