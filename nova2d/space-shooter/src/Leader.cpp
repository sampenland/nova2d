#include "Leader.h"

namespace spaceshooter
{
	Leader::Leader(std::string assetName, Vec2Int position, Vec2Int size, char layer)
	{
		AddSprite(assetName, position, size, layer);
		AddPatrolPointWithFunction(Vec2Int(position.x - 400, position.y), std::bind(&Leader::LinearPatrolMove, this));
		AddPatrolPointWithFunction(Vec2Int(position.x + 400, position.y), std::bind(&Leader::LinearPatrolMove, this));
		EnableAI(true);
		Configure(1, true);

		for (int row = 1; row <= 10; row++)
		{
			for (int col = 1; col <= 10; col++)
			{
				int	offsetX = col * 32;
				int offsetY = row * 32;

				Pawn* pawn = new Pawn("pawn", Vec2Int(offsetX, offsetY), Vec2Int(16, 16),
					0, m_Sprite, 2.0f);
				pawn->Configure(m_MoveSpeed, m_AliveBounds);
				pawn->Offset(Vec2Int(offsetX, offsetY));

				m_Pawns.push_back(pawn);

			}
			
		}

		Game::AddUpdater(std::bind(&Leader::Update, this));
	}

	Leader::~Leader()
	{
		Game::RemoveUpdater(std::bind(&Leader::Update, this));
	}
}