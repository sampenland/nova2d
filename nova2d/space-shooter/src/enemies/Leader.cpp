#include "Leader.h"
#include "ai/SimpleFollower.h"
#include "physics/Collision.h"

namespace spaceshooter
{
	Leader::Leader(std::string assetName, Vec2Int position, Vec2Int size, char layer)
	{
		AddSprite(assetName, position, size, layer);
		
		int forwardMove = 96;
		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));

		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x - 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x + 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		
		EnableAI(true);
		Configure(5, true);
		ConfigureLoopIndex(1);
		ConfigureShoot(2000, 5000);

		GeneratePawnWave(2, 3);

		ConfigureUsingBounds(false, false);
		ConfigureCollider(m_Sprite, 0, "leader");

		m_HealthBar = new SimpleStatBar(false, m_Sprite->GetX(), m_Sprite->GetY() - 2,
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

		auto moveR = n2dRandomFloat(10000, 20000);
		auto bombR = n2dRandomFloat(10000, 20000);
		m_MoveTimer = new Timer(moveR, false, std::bind(&Leader::MoveForwardThenBack, this));
		m_BombTimer = new Timer(bombR, false, std::bind(&Leader::DeployBomb, this));

		n2dAddDeleteable(this);
		n2dReferenceAdd("leader", this);
	}

	void Leader::WatchPawns()
	{
		if (m_PawnCount < 1)
		{
			int rows = n2dRandomInt(2, 5);
			int cols = 3;
			GeneratePawnWave(rows, cols);
		}
	}

	void Leader::GeneratePawnWave(char rows, char cols)
	{
		const int moveForward = 132 + (rows * 32);
		for (int row = 0; row < rows; row++)
		{
			for (int col = -cols+1; col < cols; col++)
			{
				int	offsetX = col * 96;
				int offsetY = -row * 32;

				Pawn* pawn = new Pawn("pawn", Vec2Int(((int)Game::s_Width / 2) + offsetX, offsetY), Vec2Int(16, 16), 1, 0.0f);
				offsetY += moveForward;
				pawn->AddPatrolPointWithFunction(Vec2Int(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2Int(pawn->GetX() - 200, offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2Int(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2Int(pawn->GetX() + 200, offsetY), pawn->GetLinearPatrolMove());
				pawn->AddPatrolPointWithFunction(Vec2Int(pawn->GetX(), offsetY), pawn->GetLinearPatrolMove());
				pawn->EnableAI(true);
				pawn->Configure(20, true);
				float rMin = n2dRandomFloat(1000, 3000);
				float rMax = n2dRandomFloat(5000, 8000);
				pawn->ConfigureShoot(rMin, rMax);

				m_Pawns.push_back(pawn);
				m_PawnCount++;

			}
		}
	}

	void Leader::PawnAttack()
	{
		for (size_t i = 0; i < m_Pawns.size(); i++)
		{
			if (!m_Pawns[i]->IsDeleted() == 0) continue;

			Pawn& p = *m_Pawns[i];

			p.ClearPatrol();

			int x = p.GetX();
			p.AddPatrolPointWithFunction(Vec2Int(x, Game::s_Height + 48), std::bind(p.GetLinearPatrolMove()));
			p.Configure(250, false);
			p.EnableAI(true);
		}
		
	}

	void Leader::HealthUpdate()
	{
		m_HealthBar->Update(m_Health, m_Sprite->GetX() - 24, m_Sprite->GetY() - 16);
	}

	void Leader::DeployBomb()
	{
		SimpleBulletController* bomb = new
			SimpleBulletController(
				Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 8),
				Vec2Int(m_Sprite->GetX(), Game::s_Height + 32),
				2.0f);

		bomb->AddSprite("bomb", Vec2Int(m_Sprite->GetX(), m_Sprite->GetY() + 32), Vec2Int(16, 16), 0);
		bomb->GetSprite()->ConfigureAnimation(0, 4, 1000, true);
		bomb->ConfigureCollider(bomb->GetSprite(), 0, "bomb");
		bomb->Configure(2, Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));
		
	}

	void Leader::Hurt(int damage)
	{
		SmallExplosion();

		m_Health -= damage;
		if (m_Health < 1)
		{
			n2dScoreAdd(80);
			DestroySelf();
		}
		else
		{
			n2dScoreAdd(6);
		}
	}

	void Leader::MoveForwardThenBack()
	{
		m_PatrolMemory = m_PatrolPoints;
		m_PatrolPoints.clear();

		AddPatrolPointWithFunction(Vec2Int(GetX(), GetY() + 128),
			std::bind(&SimpleWeakAI::LinearPatrolMove, this));
		
		AddPatrolPointWithFunction(Vec2Int(GetX(), GetY()), 
			std::bind(&SimpleWeakAI::LinearPatrolMove, this));
		
		ConfigureOnPatrolComplete(std::bind(&Leader::RememberOldMoving, this));
		RestartPatrol();
		Configure(10, true);

	}

	void Leader::RememberOldMoving()
	{
		m_PatrolPoints = m_PatrolMemory;
		ConfigureOnPatrolComplete(([]() {}));
		Configure(30, true);
	}

	void Leader::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", m_Sprite->GetPosition(), Vec2Int(16, 16), 0);
		explosion->ConfigureAnimation(0, 5, 100, true);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
			});
		explosion->ConfigureAnimationEnd(*animEnd);
	}

	Leader::~Leader()
	{
		
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
		Player* player = (Player*)SceneManager::s_ReferenceManager->GetReferenced("player");
		SimpleFollower* bullet = new SimpleFollower(player->GetSprite(), 0.0f);
		bullet->AddSprite("leader-bullet", Vec2Int(GetX(), GetY() + 32), Vec2Int(16, 16), 1);
		bullet->ConfigureCollider(bullet->GetSprite(), 0, "leader-bullet");
		bullet->ConfigureAliveBounds(Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));
		auto delayStart = n2dRandomFloat(0, 4000);
		bullet->Configure(1, delayStart, Vec2Int(GetX(), Game::s_Height + 32));
		bullet->ConfigureRotation(true, -90);
		
		auto onCollision = new auto ([](Collision* collision)
		{
			if ((collision->m_ColliderA->m_ColliderName == "leader-bullet" &&
				collision->m_ColliderB->m_ColliderName == "player-bullet"))
			{
				((SimpleFollower*)collision->m_ColliderA)->DestroySelf();
				((SimpleBulletController*)collision->m_ColliderB)->DestroySelf();
			}
			else if ((collision->m_ColliderB->m_ColliderName == "leader-bullet" &&
				collision->m_ColliderA->m_ColliderName == "player-bullet"))
			{
				((SimpleFollower*)collision->m_ColliderB)->DestroySelf();
				((SimpleBulletController*)collision->m_ColliderA)->DestroySelf();
			}
		});

		bullet->ConfigureOnCollision(*onCollision);

		auto bulletDestroy = new auto ([=] {
			
			if(bullet->IsDeleted() == 0)
				bullet->DestroySelf();
		
		});

		auto destructR = n2dRandomFloat(6500, 12000);
		Timer* bulletDestruct = new Timer(destructR, false, *bulletDestroy);
		bullet->AddTimer(bulletDestruct);

	}

	void Leader::DestroySelf()
	{
		if (m_Destroyed) return;

		n2dReferenceRemove("leader");

		if ((int)m_Pawns.size() > 0)
		{
			PawnAttack();
		}

		m_Destroyed = true;
		m_Alive = false;

		m_DeleteNow = 1;

		CleanUpdaters();

		if(m_MoveTimer)
			m_MoveTimer->DestroySelf();
		
		if (m_BombTimer)
			m_BombTimer->DestroySelf();

		if (m_HealthBar)
			m_HealthBar->DestroySelf();

		SimpleWeakAI::DestroySelf();
	}
}