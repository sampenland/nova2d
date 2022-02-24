#include "Play.h"
#include "../Player.h"
#include "../enemies/Leader.h"
#include "../specials/TimeWarp.h"
#include "input/ScrollSelect.h"
#include "utils/ValueManager.h"

namespace spaceshooter
{

	using namespace novazero::input;

	Play::Play(const std::string& sceneName) : Scene(sceneName) { }

	void Play::Start()
	{
		n2dPauseKeySet(SDLK_r);
		n2dScoreSet(0);

		Player::s_Player1Streak = 0;
		Player::s_Player1MaxStreak = 0;

		Player* player = new Player("player", "player1", Vec2((float)Game::s_Width / 2 - 8, (float)Game::s_Height - 64), Vec2Int(16, 16), 1);
		n2dReferenceAdd("player", player);
		AddObjectToCleanUp(player);

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);

		const int streakSize = 144;
		m_P1StreakText = new Text("font1", "P1 Streak: 0", "light-blue", Rect(Game::s_Width - scoreSize - 8, 32, scoreSize, 16), 0);

		n2dDirectorAddToStack(true, 0, "Move Speed", 70, 0.01f, 6.f, &player->m_MoveSpeed);

		AddObjectToCleanUp(m_ScoreText);
		AddObjectToCleanUp(m_P1StreakText);

	}

	void Play::Update()
	{
		m_ScoreText->UpdateText("Score: " + tostring(n2dScore));
		m_P1StreakText->UpdateText("Streak: " + std::to_string(Player::s_Player1MaxStreak));
	}

	void Play::End()
	{
		n2dPauseKeyClear();
		n2dRemoveDrawable(m_ScoreText->m_ID, 0);
		CleanUp();
	}

}