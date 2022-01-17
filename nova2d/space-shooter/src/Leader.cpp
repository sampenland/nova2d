#include "Leader.h"

namespace spaceshooter
{
	Leader::Leader(std::string assetName, Vec2Int position, Vec2Int size, char layer)
	{
		AddSprite(assetName, position, size, layer);
		
		int forwardMove = 256;
		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));

		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x - 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x + 300, position.y + forwardMove), std::bind(&Leader::LinearPatrolMove, this));
		
		EnableAI(true);
		Configure(1, true);
		ConfigureLoopIndex(1);
		ConfigureShoot(2, 3);

		for (int row = 0; row <= 2; row++)
		{
			for (int col = -3; col <= 3; col++)
			{
				int	offsetX = col * 96;
				int offsetY = -64 - (row * 32);

				Pawn* pawn = new Pawn("pawn", Vec2Int(position.x + offsetX, offsetY), Vec2Int(16, 16),
					0, m_Sprite, 0.0f);
				pawn->Configure(m_MoveSpeed + 2);
				pawn->ConfigureShoot(10);
				pawn->Offset(Vec2Int(offsetX, offsetY));

				m_Pawns.push_back(pawn);

			}
			
		}

		Game::AddUpdater(std::bind(&Leader::Update, this));
		Game::AddUpdater(std::bind(&Leader::ShootUpdate, this));
	}

	Leader::~Leader()
	{
		Game::RemoveUpdater(std::bind(&Leader::Update, this));
		Game::RemoveUpdater(std::bind(&Leader::ShootUpdate, this));
	}

	void Leader::ShootUpdate()
	{
		if (m_DelayShoot < 0)
		{
			m_DelayShoot = randomf(1, m_DelayShootMax);
			Shoot();
			return;
		}

		m_DelayShoot -= Game::s_DeltaTime;
	}

	void Leader::Shoot()
	{
		
		Player* player = (Player*)Game::s_ReferenceManager->GetReferenced("player");
		SimpleFollower* bullet = new SimpleFollower(player->GetSprite(), 0.0f);
		// Todo: fix this
		//bullet->ConfigureAliveBounds(Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));
		bullet->Configure(1);
		bullet->AddSprite("leader-bullet", Vec2Int(GetX(), GetY() + 32), Vec2Int(16, 16), 0);
		bullet->ConfigureRotation(true, -90);

		Timer* bulletDestruct = new Timer(3000, false, std::bind(&SimpleFollower::DestroySelf, bullet));
		bullet->AddTimer(bulletDestruct);

	}

	void Leader::DestroySelf()
	{
		if (m_Destroyed) return;

		m_Destroyed = true;

		Game::RemoveUpdater(std::bind(&Leader::Update, this));

		if (m_Sprite)
			delete m_Sprite;
	}
}