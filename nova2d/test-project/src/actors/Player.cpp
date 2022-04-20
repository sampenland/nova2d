#include "Player.h"
#include "core/Game.h"

namespace testproject
{
	Player::Player(Vec2 position, Vec2 size, unsigned char layer) :
		BasicController("player", "player", position, 
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
	}

	void Player::DestroySelf()
	{
		CleanUpdaters();
		BasicController::DestroySelf();
	}
}