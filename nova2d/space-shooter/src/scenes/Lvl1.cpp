#include "Lvl1.h"
#include "../Player.h"
#include "../enemies/Leader.h"
#include "maths/Vec2Int.h"
#include "graphics/Text.h"
#include "../specials/TimeWarp.h"
#include "input/ScrollSelect.h"

namespace spaceshooter
{

	using namespace novazero::input;

	Lvl1::Lvl1(const std::string& sceneName) : Scene(sceneName)
	{
		m_LeaderController = nullptr;
	}

	void Lvl1::Start()
	{
		n2dPauseKeySet(SDLK_r);
		n2dScoreSet(0);

		LeaderController::s_Wave = 0;
		LeaderController::s_LeaderExists = false;

		Leader::s_PawnCount = 0;
		Leader::s_PawnWave = 0;

		Player::s_Player1Streak = 0;
		Player::s_Player1MaxStreak = 0;

		Player* player = new Player("player", "player1", Vec2((float)Game::s_Width / 2 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
		n2dReferenceAdd("player", player);
		AddObjectToCleanUp(player);
		
		m_LeaderController = new LeaderController();
		m_Pawn1Controller = new Pawn1Controller();

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);
		
		const int streakSize = 144;
		m_P1StreakText = new Text("font1", "P1 Streak: 0", "light-blue", Rect(Game::s_Width - scoreSize - 8, 32, scoreSize, 16), 0);
		
		n2dDirectorAddToStack(false, 0, "Move Speed", 70, 0.01f, 6.f, &player->m_MoveSpeed);

		AddObjectToCleanUp(m_LeaderController);
		AddObjectToCleanUp(m_ScoreText);
		AddObjectToCleanUp(m_P1StreakText);

	}

	void Lvl1::Update()
	{
		auto score = n2dScoreGet();
		m_ScoreText->UpdateText("Score: " + std::to_string(score));
		m_P1StreakText->UpdateText("Streak: " + std::to_string(Player::s_Player1MaxStreak));
	}

	void Lvl1::End()
	{
		n2dPauseKeyClear();
		n2dRemoveDrawable(m_ScoreText->m_ID, 0);
		CleanUp();
	}

}