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
		Player* player = new Player("player", Vec2((float)Game::s_Width / 2 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
		player->Configure(1500);
		player->ConfigureMove(3);
		player->SetMoveBounds(Game::GetGameBounds());

		n2dReferenceAdd("player", player);

		/*Leader* leader = new Leader("leader", Vec2((float)Game::s_Width / 2 - 8, -48.0f), Vec2Int(16, 16), 1);*/
		m_LeaderController = new LeaderController();
		m_LeaderController->CreateLeader(Vec2((float)Game::s_Width / 2, (float)Game::s_Height / 2), 16, 1, 1);

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);
		n2dAddDrawable(m_ScoreText, 0);

		/*TimeWarp* tw = new TimeWarp(Vec2((float)Game::s_Width / 2 - 40, (float)Game::s_Height - 256), 
			0.25f, 80, 10000);*/
		
		AddObjectToCleanUp(player);
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