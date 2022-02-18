#include "Leader.h"
#include "ai/SimpleFollower.h"
#include "physics/Collision.h"
#include "../specials/LeaderController.h"
#include "../scenes/Lvl1.h"
#include "components/HitDisplay.h"

namespace spaceshooter
{
	int Leader::s_PawnCount = 0;
	int Leader::s_PawnWave = 0;
	std::vector<Pawn*> Leader::s_Pawns;

	Leader::Leader(const std::string& assetName, Vec2 position, Vec2Int size, int maxHealth, int pawnRows, int pawnCols, char layer)
	{
		SetPosition(position);
		AddSprite(assetName, position, size, layer);
		
		m_HealthMax = maxHealth;
		m_Health = maxHealth;

		int forwardMove = 96;
		AddPatrolPointWithFunction(Vec2(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));

		AddPatrolPointWithFunction(Vec2(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2(position.x - 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2(position.x + 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		
		EnableAI(true);
		Configure(5, true);
		ConfigureLoopIndex(1);
		ConfigureShoot(2000, 5000);

		GeneratePawnWave(pawnRows, pawnCols);

		ConfigureUsingBounds(false, false);
		ConfigureCollider(GetSprite(), 0, "leader");

		m_HealthBar = new SimpleStatBar(false, (int)GetX(), (int)GetY() - 2,
			64, 12, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");

		auto id = n2dAddUpdater(Leader::Update, this);
		m_CleanUpdaters.push_back(id);
		id = n2dAddUpdater(Leader::ShootUpdate, this);
		m_CleanUpdaters.push_back(id);
		id = n2dAddUpdater(Leader::HealthUpdate, this);
		m_CleanUpdaters.push_back(id);
		id = n2dAddUpdater(Leader::WatchPawns, this);
		m_CleanUpdaters.push_back(id);

		auto moveR = n2dRandomFloat(5000, 10000);
		auto bombR = n2dRandomFloat(5000, 10000);
		m_MoveTimer = new Timer(moveR, false, std::bind(&Leader::MoveForwardThenBack, this));
		m_BombTimer = new Timer(bombR, false, std::bind(&Leader::DeployBomb, this));

		n2dAddDeleteable(this);
		n2dReferenceAdd("leader", this);
	}

	void Leader::WatchPawns()
	{
		if (s_PawnWave >= 4)
		{
			return;
		}

		if (s_PawnCount < 1)
		{
			if (!m_GeneratingPawnWave)
			{
				m_GeneratingPawnWave = true;
				m_GenTimer = new Timer(1000, false, [=]() {
					
					m_GeneratingPawnWave = false;

					int rows = 2;
					int cols = 2;

					switch (s_PawnWave)
					{
					case 0:
						rows = 2;
						cols = 2;
						break;
					case 1:
						rows = 2;
						cols = 3;
						break;
					case 2:
						rows = 2;
						cols = 4;
						break;
					case 3:
						rows = 4;
						cols = 2;
						break;
					case 4:
						rows = 4;
						cols = 4;
						break;
					}

					GeneratePawnWave(rows, cols);

					s_PawnWave++;

					if (s_PawnWave >= 1)
					{
						Retreat();
					}

				});
				return;
			}
		}
	}

	void Leader::Retreat()
	{
		if (m_Retreating) return;
		m_Retreating = true;
		ClearPatrol();
		AddPatrolPointWithFunction(Vec2(GetX(), GetY()), std::bind(&SimpleWeakAI::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2(GetX(), -32), std::bind(&SimpleWeakAI::LinearPatrolMove, this));

		ConfigureAliveBounds(Game::GetGameBounds(32));
		ConfigureUsingBounds(false, true);
	}

	void Leader::GeneratePawnWave(char rows, char cols)
	{
		const int moveForward = 132 + (rows * 32);
		for (int row = 0; row < rows; row++)
		{
			for (int col = -cols+1; col < cols; col++)
			{
				float offsetX = (float)col * 48;
				float offsetY = (float)-row * 32;

				float rMin = n2dRandomFloat(6000, 8000);
				float rMax = n2dRandomFloat(8000, 12000);
				
				Pawn* pawn = new Pawn("pawn", Vec2((Game::s_Width / 2) + offsetX, offsetY), 
					Vec2Int(16, 16), 1, 0.0f, rMin, rMax);

				offsetY += moveForward;
				pawn->AddPatrolPointWithFunction(Vec2(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2(pawn->GetX() - 200, offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2(pawn->GetX() + 200, offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->EnableAI(true);
				pawn->Configure(20, true);

				s_Pawns.push_back(pawn);

			}
		}
	}

	void Leader::ClearDeadPawns()
	{
		for (std::vector<Pawn*>::iterator it = s_Pawns.begin(); it != s_Pawns.end();)
		{
			Pawn& p = **it;
			if (p.m_Dead == 1)
				it = s_Pawns.erase(it);

			it++; //TODO: crash here
		}
	}

	void Leader::PawnAttack()
	{
		ClearDeadPawns();
		for (std::vector<Pawn*>::iterator it = s_Pawns.begin(); it != s_Pawns.end();)
		{
			Pawn& p = **it;

			if (p.m_Destroyed)
			{
				it = s_Pawns.erase(it);
				continue;
			}

			p.ClearPatrol();
			
			float x = p.GetX();
			p.AddPatrolPointWithFunction(Vec2(x, (float)Game::s_Height + 48), std::bind(p.GetLinearPatrolMove()));
			p.Configure(10, false);
			p.EnableAI(true);
			p.ConfigureAliveBounds(Game::GetGameBounds());
			p.ConfigureUsingBounds(false, true);

			it++;
		}
		
	}

	void Leader::HealthUpdate()
	{
		m_HealthBar->Update((int)(((float)m_Health / m_HealthMax) * 64), (int)GetX() - 24, (int)GetY() - 16);
	}

	void Leader::DeployBomb()
	{
		SimpleBulletController* bomb = new
			SimpleBulletController(
				Vec2Int((int)GetX(), (int)GetY() + 8),
				Vec2Int((int)GetX(), (int)Game::s_Height + 32),
				2.0f);

		bomb->AddSprite("bomb", Vec2(GetX(), GetY() + 32), Vec2Int(16, 16), 0);
		bomb->GetSprite()->ConfigureAnimation(0, 4, 4, 1000, true);
		bomb->ConfigureCollider(bomb->GetSprite(), 0, "bomb");
		bomb->Configure(2, Rect(-16.f, -16.f, (float)Game::s_Width + 16.f, (float)Game::s_Height + 16.f));
		
	}

	void Leader::DisplayHit(int score, Vec2 startPos)
	{
		Rect rect = Rect(startPos.x - GetWidth() / 2.f, startPos.y + GetHeight()*2, 24.f, 16.f);
		HitDisplay* hitDisplay = new HitDisplay("+ " + std::to_string(score), "font4", "yellow", rect,
			Vec2(startPos.x, startPos.y + 64), 4000, 0);
	}

	void Leader::Hurt(int damage)
	{
		SmallExplosion();

		m_Health -= damage;
		if (m_Health < 1)
		{
			n2dScoreAdd(80);
			DisplayHit(80, GetPosition());
			DestroySelf();
		}
		else
		{
			n2dScoreAdd(12);
			DisplayHit(12, GetPosition());
		}
	}

	void Leader::MoveForwardThenBack()
	{
		m_PatrolMemory = GetPatrolPoints();
		ClearPatrol();

		AddPatrolPointWithFunction(Vec2(GetX(), GetY() + 128),
			std::bind(&SimpleWeakAI::LinearPatrolMove, this));
		
		AddPatrolPointWithFunction(Vec2(GetX(), GetY()), 
			std::bind(&SimpleWeakAI::LinearPatrolMove, this));
		
		ConfigureOnPatrolComplete(std::bind(&Leader::RememberOldMoving, this));
		RestartPatrol();
		Configure(10, true);

	}

	void Leader::RememberOldMoving()
	{
		SetAllPatrolPoints(m_PatrolMemory);
		ConfigureOnPatrolComplete(([]() {}));
		Configure(30, true);
	}

	void Leader::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", GetPosition(), Vec2Int(16, 16), 0);
		explosion->ConfigureAnimation(0, 5, 5, 100, true);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->ConfigureAnimationEnd(*animEnd);
	}

	void Leader::ShootUpdate()
	{
		if (!m_Alive) return;

		if (m_DelayShoot < 0)
		{
			auto r = n2dRandomFloat(1.0f, m_DelayShootMax);
			m_DelayShoot = r;
			Shoot();
			return;
		}

		m_DelayShoot = (float)(m_DelayShoot - Game::s_DeltaTime);
	}

	void Leader::Shoot()
	{
		if (n2dDebug) return;

		Player* player = (Player*)SceneManager::s_ReferenceManager->GetReferenced("player");
		SimpleFollower* bullet = new SimpleFollower(player->GetSprite(), 0.0f);
		bullet->AddSprite("leader-bullet", Vec2(GetX(), GetY() + 32), Vec2Int(16, 16), 1);
		bullet->ConfigureCollider(bullet->GetSprite(), 0, "leader-bullet");
		bullet->ConfigureAliveBounds(Rect(-16.f, -16.f, (float)Game::s_Width + 16.f, (float)Game::s_Height + 16.f));
		auto delayStart = n2dRandomFloat(0, 4000);
		bullet->Configure(1, delayStart, Vec2Int((int)GetX(), (int)Game::s_Height + 32));
		bullet->ConfigureRotation(true, -90);
		
		auto onCollision = new auto ([=](Collision* collision)
		{
			bool collAisPlayer1Bullet = collision->m_ColliderA->m_ColliderName == "player-bullet";
			bool collBisPlayer1Bullet = collision->m_ColliderB->m_ColliderName == "player-bullet";

			bool collAisPlayer2Bullet = collision->m_ColliderA->m_ColliderName == "player2-bullet";
			bool collBisPlayer2Bullet = collision->m_ColliderB->m_ColliderName == "player2-bullet";

			bool collAisPlayer1 = collision->m_ColliderA->m_ColliderName == "player1";
			bool collBisPlayer1 = collision->m_ColliderB->m_ColliderName == "player1";

			bool collAisPlayer2 = collision->m_ColliderA->m_ColliderName == "player2";
			bool collBisPlayer2 = collision->m_ColliderB->m_ColliderName == "player2";

			// player 1 with leader bullet
			if (collision->m_ColliderA->m_ColliderName == "leader-bullet" && 
				(collBisPlayer1 || collBisPlayer2))
			{
				((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
				((Player*)collision->m_ColliderB)->Die();
			}
			else if (collision->m_ColliderB->m_ColliderName == "leader-bullet" && 
				(collAisPlayer1 || collAisPlayer2))
			{
				((Player*)collision->m_ColliderA)->Die();
				((SimpleFollower*)collision->m_ColliderB)->DestroySelf();
			}

			if ((collision->m_ColliderA->m_ColliderName == "leader-bullet" &&
				(collBisPlayer1Bullet || collBisPlayer2Bullet)))
			{
				// leader pullet with player bullet
				DisplayHit(24, ((SimpleFollower*)collision->m_ColliderA)->GetSprite()->GetPosition());
				((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
				n2dScoreAdd(24);
			}
			else if ((collision->m_ColliderB->m_ColliderName == "leader-bullet" &&
				(collAisPlayer1Bullet || collAisPlayer2Bullet)))
			{
				// leader pullet with player bullet
				DisplayHit(24, ((SimpleFollower*)collision->m_ColliderB)->GetSprite()->GetPosition());
				((SimpleFollower*)collision->m_ColliderB)->DestroySelf();
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
				n2dScoreAdd(24);
			}
			else if (collision->m_ColliderA->m_ColliderName == "leader-bullet" &&
				collision->m_ColliderB->m_ColliderName == "leader-bullet")
			{
				// leader bullet with another leader bullet
				((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
				((SimpleFollower*)collision->m_ColliderB)->DestroySelf();
			}
		});

		bullet->ConfigureOnCollision(*onCollision);

		auto bulletDestroy = new auto ([=] {
			
			if(bullet->IsDeleted() == 0)
				bullet->DestroySelf();
		
		});

		auto destructR = n2dRandomFloatMinChance(6500.0f, 12000.0f, 0.2f);
		Timer* bulletDestruct = new Timer(destructR, false, *bulletDestroy);
		bullet->AddTimer(bulletDestruct);

	}

	void Leader::DestroySelf()
	{
		if (m_Destroyed) return;
		m_Destroyed = true;

		n2dReferenceRemove("leader");

		if ((int)s_Pawns.size() > 0)
		{
			PawnAttack();
		}

		m_Alive = false;

		LeaderController::s_LeaderExists = false;
		SetDeleted(true);

		CleanUpdaters();

		if(m_MoveTimer)
			m_MoveTimer->DestroySelf();
		
		if (m_BombTimer)
			m_BombTimer->DestroySelf();

		if (m_HealthBar)
			m_HealthBar->DestroySelf();

		if (m_GenTimer)
			m_GenTimer->DestroySelf();

		SimpleWeakAI::DestroySelf();
	}
}