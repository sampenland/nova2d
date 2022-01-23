#include "Player.h"
#include "physics/Collision.h"
#include "ai/SimpleFollower.h"
#include "enemies/Pawn.h"
#include "enemies/Leader.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::input;

	Player::Player(std::string assetName, Vec2Int position, Vec2Int size, char layer)
		: UDRLController(assetName, position, size, layer), Collider(0)
	{
		n2dAddKeyDownListener(SDLK_SPACE, Player::Shoot, this);
		n2dAddKeyDownListener(SDLK_ESCAPE, Player::Quit, this);

		if (SDL_NumJoysticks() > 0)
		{
			AddJoyEventListener(0, SDL_CONTROLLER_BUTTON_B, &InputHandler::IsJoystickButtonDown,
				std::bind(&Player::Shoot, this));
		}

		//m_Sprite->ConfigureAnimation(0, 2, 100, true);
		ConfigureCollider(m_Sprite, 0, "player");

		int startX = 8;
		int startY = 8;
		for (int i = 0; i < m_Lives; i++)
		{
			Sprite* life = new Sprite("player", Vec2Int(startX + (i * 16), startY), Vec2Int(16, 16), 0);
			m_LifeSprites.push_back(life);
		}

		m_CleanID = n2dAddUpdater(Player::Update, this);
	}

	Player::~Player()
	{
		n2dRemoveUpdater(m_CleanID);
	}

	void Player::Quit()
	{
		n2dSceneChange("mainMenu");
	}

	void Player::OnCollision(Collision* collision)
	{
		bool hit = false;
		if ((collision->m_ColliderA->m_ColliderName == "leader-bullet" && collision->m_ColliderB->m_ColliderName == "player") ||
			(collision->m_ColliderA->m_ColliderName == "pawn-bullet" && collision->m_ColliderB->m_ColliderName == "player"))
		{
			// Bullets with player
			((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
			hit = true;
		}
		else if ((collision->m_ColliderB->m_ColliderName == "leader-bullet" && collision->m_ColliderA->m_ColliderName == "player") ||
			(collision->m_ColliderB->m_ColliderName == "pawn-bullet" && collision->m_ColliderA->m_ColliderName == "player"))
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
			Sprite* s = m_LifeSprites.at(m_Lives - 1);
			s->DestroySelf();
			m_LifeSprites.pop_back();
			m_Lives--;
		}
		else if (hit)
		{
			// Game over
			auto endGame = new auto ([]() {

				n2dSceneChange("gameOver");

			});

			Timer* t = new Timer(1000, false, *endGame);
		}

	}

	void Player::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", m_Sprite->GetPosition(), Vec2Int(16, 16), 0);
		explosion->ConfigureAnimation(0, 5, 100, true);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->ConfigureAnimationEnd(*animEnd);
	}

	void Player::Update()
	{
		if (!m_CanShoot)
		{
			if (m_ShootDelay > 0)
			{
				m_ShootDelay -= Game::s_DeltaTime;
				return;
			}
			else
			{
				m_CanShoot = true;
				m_ShootDelay = m_ShootDelayReset;
			}
		}
	}

	void Player::Shoot()
	{
		if (!m_CanShoot) return;

		m_CanShoot = false;
		m_ShootDelay = m_ShootDelayReset;

		SimpleBulletController* bullet = new SimpleBulletController(Vec2Int(GetX(), GetY() - GetHeight()), Vec2Int(GetX(), -GetHeight()), 4);
		bullet->Configure(20, Rect(0, 0, Game::s_Width, Game::s_Height));
		bullet->AddSprite("player-bullet", Vec2Int(GetX(), GetY() - GetHeight()), Vec2Int(16, 16), 1);
		bullet->ConfigureCollider(bullet->GetSprite(), 0, "player-bullet");
		bullet->ConfigureAliveBounds(Game::GetGameBounds());

		auto collisionFunction = new auto ([](Collision* collision) {

			// Bullet with bullet
			if ((collision->m_ColliderA->m_ColliderName == "player-bullet" &&
				collision->m_ColliderB->m_ColliderName == "pawn-bullet") ||
				(collision->m_ColliderB->m_ColliderName == "player-bullet" &&
					collision->m_ColliderA->m_ColliderName == "pawn-bullet"))
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
			}
			
			// Bullet with pawn
			if ((collision->m_ColliderA->m_ColliderName == "player-bullet" &&
				collision->m_ColliderB->m_ColliderName == "pawn"))
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((Pawn*)collision->m_ColliderB)->Hurt(4);
			}
			else if ((collision->m_ColliderB->m_ColliderName == "player-bullet" &&
				collision->m_ColliderA->m_ColliderName == "pawn"))
			{
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				((Pawn*)collision->m_ColliderA)->Hurt(4);
			}

			// Bullet with leader
			if ((collision->m_ColliderA->m_ColliderName == "player-bullet" &&
				collision->m_ColliderB->m_ColliderName == "leader"))
			{
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				((Leader*)collision->m_ColliderB)->Hurt(2);
			}
			else if ((collision->m_ColliderB->m_ColliderName == "player-bullet" &&
				collision->m_ColliderA->m_ColliderName == "leader"))
			{
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				((Leader*)collision->m_ColliderA)->Hurt(2);
			}

		});

		bullet->ConfigureOnCollision(*collisionFunction);

	}
}