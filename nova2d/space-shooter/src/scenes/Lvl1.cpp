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
			player1->Configure(1500);
			player1->ConfigureMove(3);
			player1->SetMoveBounds(Game::GetGameBounds());

			n2dReferenceAdd("player1", player1);
			AddObjectToCleanUp(player1);
		}
		else
		{
			Player* player1 = new Player("player", "player1", Vec2((float)Game::s_Width / 3 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
			player1->Configure(1500);
			player1->ConfigureMove(3);
			player1->SetMoveBounds(Game::GetGameBounds());
			player1->EnableArrowKeys(false);

			n2dReferenceAdd("player1", player1);
			AddObjectToCleanUp(player1);

			Player* player2 = new Player("player", "player2", Vec2((float)Game::s_Width - Game::s_Width / 3 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
			player2->Configure(1500);
			player2->ConfigureMove(3);
			player2->SetMoveBounds(Game::GetGameBounds());
			player2->EnableWASD(false);

			n2dReferenceAdd("player2", player2);
			AddObjectToCleanUp(player2);
		}
		
		m_LeaderController = new LeaderController();
		m_LeaderController->CreateLeader(Vec2((float)Game::s_Width / 2, (float)Game::s_Height / 2), 16, 1, 1);

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);
		n2dAddDrawable(m_ScoreText, 0);

		/*TimeWarp* tw = new TimeWarp(Vec2((float)Game::s_Width / 2 - 40, (float)Game::s_Height - 256), 
			0.25f, 80, 10000);*/

		AddObjectToCleanUp(m_LeaderController);
		AddObjectToCleanUp(m_ScoreText);

	}

	void Lvl1::Update()
	{
		auto score = n2dScoreGet();
		m_ScoreText->UpdateText("Score: " + std::to_string(score));
	}

	void Lvl1::End()
	{
		n2dRemoveDrawable(m_ScoreText->m_ID, 0);
		CleanUp();
	}

}