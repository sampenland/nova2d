#include "LeaderController.h"

namespace spaceshooter
{
	bool LeaderController::s_LeaderExists = false;

	LeaderController::LeaderController()
		: Deleteable("leader-controller")
	{
		auto cleanID = n2dAddUpdater(LeaderController::Update, this);
		m_CleanUpdaters.push_back(cleanID);
	}

	void LeaderController::CreateLeader(Vec2 position, int maxHealth, int pawnRows, int pawnCols)
	{
		m_Leader = new Leader("leader", Vec2((float)Game::s_Width / 2 - 8, -48.0f), Vec2Int(16, 16), maxHealth, pawnRows, pawnCols, 1);
		if (m_Leader)
		{
			s_LeaderExists = true;
		}
	}

	void LeaderController::Update()
	{
		if (!IsEnabled()) return;

		if (!s_LeaderExists)
		{
			m_Wave++;
		
			int row = n2dRandomInt(1, m_Wave);
			int col = n2dRandomInt(1, m_Wave);
			if (row > 6)row = 6;
			if (col > 4)col = 4;
			CreateLeader(Vec2((float)Game::s_Width / 2, (float)Game::s_Height / 2), 32, row, col);
		}
	}

	void LeaderController::DestroySelf()
	{
		CleanUpdaters();

		if (m_Leader)
			m_Leader->DestroySelf();

		SetDeleted(true);
	}
}