#include "Player.h"
#include "physics/Collision.h"
#include "ai/SimpleFollower.h"
#include "enemies/Pawn.h"
#include "enemies/Leader.h"
#include "specials/PawnBullet.h"
#include "scenes/Lvl1.h"
#include "specials/TimeWarp.h"
#include "enemies/Pawn1.h"
#include "components/HitDisplay.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::input;

	Uint32 Player::s_Player1LastPawnKillTime = 0;
	
	int Player::s_Player1Streak = 0;
	int Player::s_Player1MaxStreak = 0;

	Player::Player(const std::string& assetName, const std::string& playerNumber, Vec2 position, Vec2Int size, char layer)
		: UDRLController(assetName, position, size, layer), Collider(0)
	{

		m_StreakSprite = new Sprite("streaks", Vec2(0.f, 0.f), Vec2Int(48, 8), 0);
		m_StreakSprite->ConfigureAnimation(0, 16, 16, 0, false);
		m_StreakSprite->ConfigureAnimating(false);

		n2dAddKeyDownListener(SDLK_SPACE, Player::OnSpace, this);
		n2dAddKeyUpListener(SDLK_SPACE, Player::OnSpaceUp, this);

		n2dAddKeyDownListener(SDLK_ESCAPE, Player::Quit, this);

		if (SDL_NumJoysticks() > 0)
		{
			AddJoyEventListener(0, SDL_CONTROLLER_BUTTON_B, &InputHandler::IsJoystickButtonDown,
				std::bind(&Player::Shoot, this));
		}

		int startX = 8;
		int startY = 8;
		for (int i = 0; i < m_Lives; i++)
		{
			Sprite* life = new Sprite("player", Vec2((float)startX + (i * 16), (float)startY), Vec2Int(16, 16), 0);
			m_LifeSprites.push_back(life);
		}

		m_Sprite->ConfigureAnimation(0, 2, 8, 100, true);
		ConfigureCollider(m_Sprite, 0, "player1");
		SetTimeEffectEnabled(false);
		
		ConfigureMove(2.f, TweenTypes::EaseInExpo, 200.f, 0.5f);
		SetMoveBounds(Game::GetGameBounds());

		m_ShootTimer = new Timer(SHOOT_TIME, true, std::bind(&Player::Shoot, this));

		m_CleanID = n2dAddUpdater(Player::Update, this);

	}

	Player::~Player()
	{
		n2dRemoveUpdater(m_CleanID);
		UDRLController::DestroySelf();
	}

	void Player::DisplayHit(int score, Vec2 pos, const std::string& fontColor)
	{
		Rect rect = Rect(pos.x - (float)GetWidth() / 2.f, pos.y - 16.f, 24.f, 16.f);
		HitDisplay* hitDisplay = new HitDisplay("+ " + std::to_string(score), "font4", fontColor, rect,
			Vec2(GetX(), GetY() - 128), 4000, 0);
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
			posIfNotPlayer = m_Sprite->GetPosition();
		}

		Sprite* explosion = new Sprite("explode", posIfNotPlayer, Vec2Int(16, 16), 0);
		explosion->ConfigureAnimation(0, 5, 5, 100, true);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->ConfigureAnimationEnd(*animEnd);
	}

	void Player::Update()
	{
		m_StreakSprite->SetPosition(Vec2(GetX() - 16, GetY() + 24));
		m_StreakSprite->JumpToFrame(s_Player1Streak);

		// Display moving
		if (n2dIsKeyDown(SDLK_w) || n2dIsKeyDown(SDLK_UP) && m_Moving != PlayerMoving::UP)
		{
			m_Sprite->JumpToFrame(0);
		}

		if (n2dIsKeyDown(SDLK_s) || n2dIsKeyDown(SDLK_DOWN) && m_Moving != PlayerMoving::DOWN)
		{
			m_Sprite->JumpToFrame(6);
		}

		if (n2dIsKeyDown(SDLK_d) || n2dIsKeyDown(SDLK_RIGHT) && m_Moving != PlayerMoving::RIGHT)
		{
			m_Sprite->JumpToFrame(4);
		}

		if (n2dIsKeyDown(SDLK_a) || n2dIsKeyDown(SDLK_LEFT) && m_Moving != PlayerMoving::LEFT)
		{
			m_Sprite->JumpToFrame(2);
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

			TimeWarp* clock = new TimeWarp(Vec2(GetX() + GetWidth() / 2, GetY() + GetHeight() / 2), 0.15f,
				maxSize, 1000, 12 * 1000); // 1/8 speed for 12 seconds
		}
	}

	void Player::Die()
	{
		Sprite* s = m_LifeSprites.at(m_Lives - 1);
		s->DestroySelf();
		m_LifeSprites.pop_back();
		m_Lives--;

		SetPosition((float)Game::s_Width / 2 - GetWidth() / 2, (float)Game::s_Height - 64);

	}

	void Player::Shoot()
	{
		int shootDir = (int)-GetHeight() - 64;
		bool downShoot = false;
		if (n2dIsKeyDown(SDLK_f))
		{
			shootDir = Game::s_Height + GetHeight() + 64;
			downShoot = true;
		}

		// create and shoot bullet
		Vec2 bulletCreatePos = Vec2(GetX(), GetY() - GetHeight());
		if (downShoot)
		{
			bulletCreatePos = Vec2(GetX(), GetY() + GetHeight());
		}

		SimpleBulletController* bullet = new SimpleBulletController(Vec2Int((int)GetX(), (int)GetY() - GetHeight()), Vec2Int((int)GetX(), shootDir), 4);
		bullet->Configure(14, Rect(0, 0, Game::s_Width, Game::s_Height));
		bullet->AddSprite("player-bullet", bulletCreatePos, Vec2Int(16, 16), 1);

		if (downShoot)
		{
			bullet->GetSprite()->Flip(SDL_FLIP_VERTICAL);
		}

		bullet->ConfigureCollider(bullet->GetSprite(), 0, "player-bullet");
		bullet->ConfigureAliveBounds(Game::GetGameBounds(32));
		bullet->SetTimeEffectEnabled(false);

		auto collisionFunction = new auto ([=](Collision* collision) {

			bool collAisPlayer1Bullet = collision->m_ColliderA->m_ColliderName == "player-bullet";
			bool collBisPlayer1Bullet = collision->m_ColliderB->m_ColliderName == "player-bullet";

			// Bullet with pawn bullet
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "pawn-bullet")
			{
				DisplayHit(2, ((PawnBullet*)collision->m_ColliderA)->GetSprite()->GetPosition(), "green");
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((PawnBullet*)collision->m_ColliderB)->DestroySelf();
				SmallExplosion(((PawnBullet*)collision->m_ColliderB)->GetSprite()->GetPosition());
				n2dScoreAdd(2);
			}
			else if(((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "pawn-bullet"))
			{
				DisplayHit(2, ((PawnBullet*)collision->m_ColliderA)->GetSprite()->GetPosition(), "green");
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				((PawnBullet*)collision->m_ColliderA)->DestroySelf();
				SmallExplosion(((PawnBullet*)collision->m_ColliderA)->GetSprite()->GetPosition());
				n2dScoreAdd(2);
			}

			// Bullet with pawn1-bullet
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "pawn1-bullet")
			{
				DisplayHit(25, ((SimpleWeakAI*)collision->m_ColliderB)->GetSprite()->GetPosition(), "white");
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				SmallExplosion(((SimpleWeakAI*)collision->m_ColliderB)->GetSprite()->GetPosition());
				((SimpleWeakAI*)collision->m_ColliderB)->DestroySelf();
				n2dScoreAdd(25);
			}
			else if (((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "pawn1-bullet"))
			{
				DisplayHit(25, ((SimpleWeakAI*)collision->m_ColliderA)->GetSprite()->GetPosition(), "white");
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				SmallExplosion(((SimpleWeakAI*)collision->m_ColliderA)->GetSprite()->GetPosition());
				((SimpleWeakAI*)collision->m_ColliderA)->DestroySelf();
				n2dScoreAdd(25);
			}

			// Bullet with leader bullet
			// more handled on Leader Shoot() bullet lamda collision
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "leader-bullet")
			{
				SmallExplosion(((SimpleFollower*)collision->m_ColliderB)->GetSprite()->GetPosition());
			}
			else if (((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "leader-bullet"))
			{
				SmallExplosion(((SimpleFollower*)collision->m_ColliderA)->GetSprite()->GetPosition());
			}
			
			// Bullet with pawn
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "pawn")
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((Pawn*)collision->m_ColliderB)->Hurt(4);
			}
			else if ((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "pawn")
			{
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				((Pawn*)collision->m_ColliderA)->Hurt(4);
			}

			// Bullet with pawn1
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "pawn1")
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				SmallExplosion(((Pawn1*)collision->m_ColliderB)->GetPosition());
				((Pawn1*)collision->m_ColliderB)->Hurt(4);
			}
			else if ((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "pawn1")
			{
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				SmallExplosion(((Pawn1*)collision->m_ColliderA)->GetPosition());
				((Pawn1*)collision->m_ColliderA)->Hurt(4);
			}

			// Bullet with leader
			if ((collAisPlayer1Bullet) && collision->m_ColliderB->m_ColliderName == "leader")
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((Leader*)collision->m_ColliderB)->Hurt(2);
			}
			else if ((collBisPlayer1Bullet) && collision->m_ColliderA->m_ColliderName == "leader")
			{
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				((Leader*)collision->m_ColliderA)->Hurt(2);
			}

		});

		bullet->ConfigureOnCollision(*collisionFunction);

	}
}