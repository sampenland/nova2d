#include "Lvl1.h"
#include "../Player.h"
#include "../enemies/Leader.h"
#include "maths/Vec2Int.h"
#include "graphics/Text.h"
#include "../specials/TimeWarp.h"

namespace spaceshooter
{
	char Lvl1::s_Players = 1;

	Lvl1::Lvl1(std::string sceneName) : Scene(sceneName)
	{
		m_LeaderController = nullptr;
	}

	void Lvl1::Start()
	{
		if (s_Players == 1)
		{
			Player* player1 = new Player("player", "player1", Vec2((float)Game::s_Width / 2 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
			n2dReferenceAdd("player1", player1);
			AddObjectToCleanUp(player1);
		}
		else
		{
			Player* player1 = new Player("player", "player1", Vec2((float)Game::s_Width / 3 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
			player1->EnableArrowKeys(false);

			n2dReferenceAdd("player1", player1);
			AddObjectToCleanUp(player1);

			Player* player2 = new Player("player", "player2", Vec2((float)Game::s_Width - Game::s_Width / 3 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
			player2->EnableWASD(false);

			n2dReferenceAdd("player2", player2);
			AddObjectToCleanUp(player2);
		}
		
		m_LeaderController = new LeaderController();

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);
		
		const int streakSize = 144;
		m_P1StreakText = new Text("font1", "P1 Streak: 0", "light-blue", Rect(Game::s_Width - scoreSize - 8, 32, scoreSize, 16), 0);
		
		if(s_Players != 1)
			m_P2StreakText = new Text("font1", "P2 Streak: 0", "light-blue", Rect(Game::s_Width - scoreSize - 8, 48, scoreSize, 16), 0);

		AddObjectToCleanUp(m_LeaderController);
		AddObjectToCleanUp(m_ScoreText);
		AddObjectToCleanUp(m_P1StreakText);

		if(s_Players != 1)
			AddObjectToCleanUp(m_P2StreakText);

	}

	void Lvl1::Update()
	{
		auto score = n2dScoreGet();
		m_ScoreText->UpdateText("Score: " + std::to_string(score));
		m_P1StreakText->UpdateText("P1 Streak: " + std::to_string(Player::s_Player1MaxStreak));
		
		if(s_Players != 1)
			m_P2StreakText->UpdateText("P2 Streak: " + std::to_string(Player::s_Player2MaxStreak));
	}

	void Lvl1::End()
	{
		n2dRemoveDrawable(m_ScoreText->m_ID, 0);
		CleanUp();
	}

}