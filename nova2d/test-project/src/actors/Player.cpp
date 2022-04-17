#include "Player.h"
#include "core/Game.h"

namespace testproject
{
	Player::Player(Vec2 position, Vec2Int size, unsigned char layer)
		: PhySprite("player", position, size, layer, Vec2Int(128, 128))
	{
		ConfigurePhysicsRect("player", false);
		
		if (GetPhySprite())
		{
			GetPhySprite()->AddAnimation("up", 0, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("right", 2, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("left", 4, 2, 1, true, nullptr);
			GetPhySprite()->AddAnimation("down", 6, 2, 1, true, nullptr);
		}

		auto cid = n2dAddUpdater(Player::Update, this);
		m_CleanUpdaters.push_back(cid);

		m_HealthBar = new SimpleStatBar(true, 0, 0, 5, 32, "space-black", "space-black",
			"green", 4);
		m_HealthBar->ConfigureForeground("green", "yellow", "red");

		for (int i = 0; i < 5; i++)
		{
			m_FuelDisplay[i] = new Image("fuel", Vec2(0, 0), Vec2Int(16, 16), 4);
		}
	}

	void Player::Update()
	{
		m_HealthBar->Update(m_Health/100 * 32, GetX() + GetWidth() + 5, GetY());

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

		Controls();
	}

	void Player::Controls()
	{
		bool up = n2dIsKeyDown(SDLK_UP);
		bool down = n2dIsKeyDown(SDLK_DOWN);
		bool right = n2dIsKeyDown(SDLK_RIGHT);
		bool left = n2dIsKeyDown(SDLK_LEFT);

		if (n2dIsKeyDown(SDLK_a))
		{
			ApplyAngularForce(-60);
		}

		if (n2dIsKeyDown(SDLK_d))
		{
			ApplyAngularForce(60);
		}

		if (!up && !down && !right && !left)
		{
			if (GetPhySprite())
			{
				GetPhySprite()->StopAnimation();
				GetPhySprite()->JumpToFrame(1);
			}
			
			return;
		}

		if (GetPhySprite())
			GetPhySprite()->StartAnimation();

		if (n2dIsKeyDown(SDLK_UP))
		{
			ApplyForce(100, Directions::Up);
			if (GetPhySprite())
				GetPhySprite()->ChangeAnimation("up");
		}

		if (n2dIsKeyDown(SDLK_DOWN))
		{
			ApplyForce(100, Directions::Down);
			if (GetPhySprite())
				GetPhySprite()->ChangeAnimation("down");
		}

		if (n2dIsKeyDown(SDLK_LEFT))
		{
			ApplyForce(100, Directions::Left);
			if (GetPhySprite())
				GetPhySprite()->ChangeAnimation("left");
			
		}

		if (n2dIsKeyDown(SDLK_RIGHT))
		{
			ApplyForce(100, Directions::Right);
			if (GetPhySprite())
				GetPhySprite()->ChangeAnimation("right");
		}
	}

	void Player::DestroySelf()
	{
		CleanUpdaters();
		PhySprite::DestroySelf();
	}
}