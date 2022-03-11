#include "Player.h"
#include "physics/Collision.h"
#include "ai/SimpleFollower.h"
#include "specials/TimeWarp.h"
#include "components/HitDisplay.h"
#include "utils/ValueManager.h"
#include "enemies/pawns/Pawn.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::input;
	using namespace novazero::components;

	Uint32 Player::s_Player1LastPawnKillTime = 0;
	
	int Player::s_Player1Streak = 0;
	int Player::s_Player1MaxStreak = 0;

	Player::Player(const std::string& assetName, const std::string& playerNumber, Vec2 position, Vec2Int size, char layer)
		: UDRLController(assetName, position, size, layer), Collider(0)
	{
		GetSprite()->Scale(2.f);
		ConfigureMoveOffsets(Origins::Centered, GetSprite());

		m_StreakSprite = new Sprite("streaks", Vec2(0.f, 0.f), Vec2Int(48, 8), 0);
		m_StreakSprite->Scale(2.f);
		m_StreakSprite->AddAnimation("streaks", 0, 16, 0, false, nullptr, true);
		m_StreakSprite->StopAnimation();
		m_StreakSprite->JumpToFrame(0);

		m_FuelDisplay = new SimpleStatBar(false, 0, Game::s_Height - 40, Game::s_Width, 48, "white", "blue", "light-blue", 0);
		m_FuelDisplayMain = new SimpleStatBar(false, 48, 0, Game::s_Width - FUEL_RIGHT_PADDING, 16, "black", "blue", "red", 0);
		m_FuelTank = new Sprite("fuel-tank", Vec2(12, Game::s_Height - 40), Vec2Int(16, 16), 0);
		m_FuelTank->Scale(2.f);

		n2dAddKeyDownListener(SDLK_SPACE, Player::OnSpace, this);
		n2dAddJoyKeyDownListener(0, SDL_CONTROLLER_BUTTON_A, Player::OnSpace, this);
		n2dAddKeyUpListener(SDLK_SPACE, Player::OnSpaceUp, this);
		n2dAddJoyKeyUpListener(0, SDL_CONTROLLER_BUTTON_A, Player::OnSpaceUp, this);

		n2dAddKeyDownListener(SDLK_ESCAPE, Player::Quit, this);

		int startX = 8;
		int startY = 8;
		char padding = 32;
		for (int i = 0; i < m_Lives; i++)
		{
			Sprite* life = new Sprite("player", Vec2((float)startX + (i * padding), (float)startY), Vec2Int(16, 16), 0);
			life->Scale(2.f);
			m_LifeSprites.push_back(life);
		}

		const float animationSpeed = 100.f;
		GetSprite()->AddAnimation("up", 0, 2, animationSpeed, true, nullptr);
		GetSprite()->AddAnimation("left", 2, 2, animationSpeed, true, nullptr, false);
		GetSprite()->AddAnimation("right", 4, 2, animationSpeed, true, nullptr, false);
		GetSprite()->AddAnimation("down", 6, 2, animationSpeed, true, nullptr, false);

		ConfigureCollider(GetSprite(), 0, "player");
		SetTimeEffectEnabled(false);
		
		ConfigureMove(3.f, TweenTypes::EaseOutQuart, 100.f, 100.f);
		SetMoveBounds(Game::GetGameBounds());

		m_ShootTimer = new Timer(SHOOT_TIME, true, std::bind(&Player::Shoot, this));

		m_CleanID = n2dAddUpdater(Player::Update, this);

	}

	Player::~Player()
	{
		n2dRemoveUpdater(m_CleanID);
		m_StreakSprite->DestroySelf();
		m_FuelTank->DestroySelf();
		m_FuelDisplay->DestroySelf();
		UDRLController::DestroySelf();
	}

	void Player::DisplayHit(int score, Vec2 pos, const std::string& fontColor)
	{
		Rect rect = Rect(pos.x - (float)GetSprite()->GetWidth() / 2.f, pos.y - 16.f, 24.f, 16.f);
		HitDisplay* hitDisplay = new HitDisplay("+ " + std::to_string(score), "font4", fontColor, rect,
			Vec2(pos.x, pos.y - 128), 4000, 0);
	}

	void Player::Quit()
	{
		n2dSceneChange("mainMenu");
	}

	void Player::OnCollision(Collision* collision)
	{
		bool collAisPlayer = collision->m_ColliderA->m_ColliderName == "player";
		bool collBisPlayer = collision->m_ColliderB->m_ColliderName == "player";

		bool hit = false;
		if ((collision->m_ColliderA->m_ColliderName == "leader-bullet" && collBisPlayer) ||
			(collision->m_ColliderA->m_ColliderName == "pawn-bullet" && collBisPlayer))
		{
			// Bullets with player
			((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
			hit = true;
		}
		else if ((collision->m_ColliderB->m_ColliderName == "leader-bullet" && collAisPlayer) ||
			(collision->m_ColliderB->m_ColliderName == "pawn-bullet" && collAisPlayer))
		{
			// Bullets with player
			((SimpleFollower*)collision->m_ColliderB)->DestroySelf();
			hit = true;
		}

		if (hit)
		{
			SmallExplosion();
		}

		if (hit && m_Lives > 1)
		{
			Die();
		}
		else if (hit)
		{
			m_ShootTimer->DestroySelf();

			// Game over
			auto endGame = new auto ([]() {

				n2dSceneChange("gameOver");

			});

			Timer* t = new Timer(1000, false, *endGame);
		}
	}

	void Player::SmallExplosion(Vec2 posIfNotPlayer)
	{
		if (posIfNotPlayer.x == -100)
		{
			posIfNotPlayer = GetSprite()->GetPosition();
		}

		Sprite* explosion = new Sprite("explode", posIfNotPlayer, Vec2Int(16, 16), 0);
		explosion->Scale(2.f);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->AddAnimation("explode", 0, 5, 100.f, false, *animEnd);
	}

	void Player::Update()
	{
		m_StreakSprite->SetPosition(Vec2(GetSprite()->GetX() - 32, GetSprite()->GetY() + 48));
		m_StreakSprite->JumpToFrame(s_Player1Streak);

		if (m_Fuel > 0.f)
		{
			m_Fuel -= n2dDeltaTime / 1000.f;
		}
		else
		{
			Die();
			return;
		}

		m_FuelDisplayMain->Update(((int)(m_Fuel / 100 * (Game::s_Width - FUEL_RIGHT_PADDING))), 48, Game::s_Height - 24);

		// Display moving
		if (n2dIsKeyDown(SDLK_UP))
		{
			GetSprite()->ChangeAnimation("up");
		}

		if (n2dIsKeyDown(SDLK_DOWN))
		{
			GetSprite()->ChangeAnimation("down");
		}

		if (n2dIsKeyDown(SDLK_RIGHT))
		{
			GetSprite()->ChangeAnimation("right");
		}

		if (n2dIsKeyDown(SDLK_LEFT))
		{
			GetSprite()->ChangeAnimation("left");
		}
	}

	void Player::OnSpace()
	{
		bool justDown = !m_SpacePressed;
		m_SpacePressed = true;
	}

	void Player::OnSpaceUp()
	{
		bool justUp = m_SpacePressed;
		if (!justUp) return;

		m_SpacePressed = false;

		int maxSize = 30;
		if (s_Player1Streak == 0) return;
		maxSize = s_Player1Streak * 30;

		if (maxSize < 60) maxSize = 60;
		if (maxSize > 120) maxSize = 150;

		if (justUp)
		{
			s_Player1Streak = 0;

			TimeWarp* clock = new TimeWarp(Vec2(GetX() + GetSprite()->GetWidth() / 2, GetY() + GetSprite()->GetHeight() / 2), 0.15f,
				maxSize, 1000, 12 * 1000); // 1/8 speed for 12 seconds
		}
	}

	void Player::Die()
	{
		if (m_Lives - 1 <= 0)
		{
			n2dSceneChange("gameOver");
			return;
		}

		Sprite* s = m_LifeSprites.at(m_Lives - 1);
		s->DestroySelf();
		m_LifeSprites.pop_back();
		m_Lives--;

		
		SetPosition(Vec2((float)Game::s_Width / 2 - GetSprite()->GetWidth() / 2, (float)Game::s_Height - 64));

	}

	void Player::Shoot()
	{
		int shootDir = (int)-GetSprite()->GetHeight() - 64;
		bool downShoot = false;
		if (n2dIsKeyDown(SDLK_f) || n2dIsJoyKeyDown(0, SDL_CONTROLLER_BUTTON_X))
		{
			shootDir = Game::s_Height + GetSprite()->GetHeight() + 64;
			downShoot = true;
		}

		// create and shoot bullet
		Vec2 bulletCreatePos = Vec2(GetSprite()->GetX(), GetSprite()->GetY() - GetSprite()->GetHeight());
		if (downShoot)
		{
			bulletCreatePos = Vec2(GetSprite()->GetX(), GetSprite()->GetY() + GetSprite()->GetHeight());
		}

		SimpleBulletController* bullet = new SimpleBulletController(Vec2Int(GetSprite()->GetX(), GetSprite()->GetY() - GetSprite()->GetHeight()), Vec2Int((int)GetSprite()->GetX(), shootDir), 4);
		bullet->Configure(14, Rect(0, 0, Game::s_Width, Game::s_Height));
		bullet->AddSprite("player-bullet", bulletCreatePos, Vec2Int(16, 16), 1);
		bullet->GetSprite()->Scale(2.f);

		if (downShoot)
		{
			bullet->GetSprite()->Flip(SDL_FLIP_VERTICAL);
		}

		bullet->ConfigureCollider(bullet->GetSprite(), 0, "player-bullet");
		bullet->ConfigureAliveBounds(Game::GetGameBounds(32));
		bullet->SetTimeEffectEnabled(false);

		auto collisionFunction = new auto ([=](Collision* collision) {

			//refs
			Collider& a = *collision->m_ColliderA;
			Collider& b = *collision->m_ColliderB;

			// whats
			bool aIsPlayerBullet = a.m_ColliderName == "player-bullet";
			bool bIsPlayerBullet = b.m_ColliderName == "player-bullet";

			bool aIsPawn = a.m_ColliderName == "pawn";
			bool bIsPawn = b.m_ColliderName == "pawn";

			if (aIsPlayerBullet && bIsPawn)
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((Pawn*)collision->m_ColliderB)->Hurt(m_ShootDamage);
			}

			if (bIsPlayerBullet && aIsPawn)
			{
				((Pawn*)collision->m_ColliderA)->Hurt(m_ShootDamage);
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
			}

		});

		bullet->ConfigureOnCollision(*collisionFunction);

	}

}