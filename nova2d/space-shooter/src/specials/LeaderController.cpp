#include "LeaderController.h"

namespace spaceshooter
{
	bool LeaderController::s_LeaderExists = false;
	int LeaderController::s_Wave = 0;

	LeaderController::LeaderController()
		: Deleteable("leader-controller")
	{
		auto cleanID = n2dAddUpdater(LeaderController::Update, this);
		m_CleanUpdaters.push_back(cleanID);

		m_Waves = new Text("font1", "", "white", Rect(Game::s_Width / 2 - 96, Game::s_Height / 2 - 32, 192, 64),
			0);

		ShowWaveAnimation();
	}

	void LeaderController::CreateLeader(Vec2 position, int maxHealth, int pawnRows, int pawnCols)
	{
		m_Leader = new Leader("leader", Vec2((float)Game::s_Width / 2 - 8, -48.0f), Vec2Int(16, 16), maxHealth, pawnRows, pawnCols, 1);
		
		int min = 4;
		int max = 8;
		switch (s_Wave)
		{
		case 1:
			min = 4;
			max = 8;
			break;
		case 2:
			min = 4;
			max = 8;
			break;
		case 3:
			min = 4;
			max = 8;
			break;
		case 4:
			min = 4;
			max = 8;
			break;
		case 5:
			min = 4;
			max = 8;
			break;
		case 6:
			min = 4;
			max = 8;
			break;
		case 7:
			min = 4;
			max = 8;
			break;
		case 8:
			min = 4;
			max = 8;
			break;
		case 9:
			min = 4;
			max = 8;
			break;
		case 10:
			min = 4;
			max = 8;
			break;
		default:
			min = 4;
			max = 8;
			break;
		}

		m_Leader->ConfigureShoot((float)min * 1000, (float)max * 1000);
		if (m_Leader)
		{
			s_LeaderExists = true;
		}
	}

	void LeaderController::Update()
	{
		if (n2dDebug) return;

		if (!IsEnabled()) return;

		if (!s_LeaderExists)
		{
			Leader::s_PawnWave = 0;

			char rows = 0;
			char cols = 0;

			switch (s_Wave)
			{
			case 0: // Wave 1
				rows = 2;
				cols = 3;
				break;
			case 1: // Wave 2
				rows = 2;
				cols = 2;
				break;
			case 2:
				rows = 2;
				cols = 3;
				break;
			case 3:
				rows = 2;
				cols = 4;
				break;
			case 4:
				rows = 2;
				cols = 5;
				break;
			case 5:
				rows = 3;
				cols = 3;
				break;
			case 6:
				rows = 3;
				cols = 4;
				break;
			case 7:
				rows = 4;
				cols = 3;
				break;
			case 8:
				rows = 4;
				cols = 4;
				break;
			case 9:
				rows = 4;
				cols = 6;
				break;
			case 10:
				rows = 5;
				cols = 6;
				break;
			}

			CreateLeader(Vec2((float)Game::s_Width / 2, (float)Game::s_Height / 2), 32, rows, cols);
			ShowWaveAnimation();

			s_Wave++;

		}
	}

	void LeaderController::ShowWaveAnimation()
	{
		m_Waves->UpdateText("Wave " + std::to_string(s_Wave + 1));
		
		Timer* hideText = new Timer(2000, false, [=]() {
			m_Waves->UpdateText("");
		});
		//TODO: tween alpha from 0-1 and 1-0
	}

	void LeaderController::DestroySelf()
	{
		CleanUpdaters();

		if (m_Leader)
			m_Leader->DestroySelf();

		SetDeleted(true);
	}
}