#include "Play.h"
#include "../Player.h"
#include "../specials/TimeWarp.h"
#include "input/ScrollSelect.h"
#include "utils/ValueManager.h"
#include "utils/timeline/events/TimelineCreateEvent.h"
#include "utils/timeline/events/TimelineExecuteEvent.h"
#include "../enemies/pawns/PawnController.h"

namespace spaceshooter
{

	using namespace novazero::input;
	using namespace novazero::utils::timeline::events;

	Play::Play(const std::string& sceneName) : Scene(sceneName) { }

	void Play::Start()
	{
		n2dPauseKeySet(SDLK_r);
		n2dScoreSet(0);

		Player::s_Player1Streak = 0;
		Player::s_Player1MaxStreak = 0;

		Player* player = new Player("player", "player1", Vec2((float)Game::s_Width / 2 - 8, (float)Game::s_Height - 96), Vec2Int(16, 16), 1);
		n2dReferenceAdd("player", player);
		AddObjectToCleanUp(player);

		const int scoreSize = 128;
		m_ScoreText = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);

		const int streakSize = 144;
		m_P1StreakText = new Text("font1", "P1 Streak: 0", "light-blue", Rect(Game::s_Width - scoreSize - 8, 32, scoreSize, 16), 0);

		m_Waves = new Text("font1", "", "white", Rect(Game::s_Width / 2 - 96, Game::s_Height / 2 - 32, 192, 64), 0);

		n2dDirectorAddToStack(true, 0, "Move Speed", 70, 0.01f, 6.f, &player->m_MoveSpeed);

		AddObjectToCleanUp(m_ScoreText);
		AddObjectToCleanUp(m_P1StreakText);
		AddObjectToCleanUp(m_Waves);

		m_PawnController = new PawnController();
		m_KamikazeController = new KamikazeController(player);

		Timer* startWaves = new Timer(1000, false, n2dMakeFunc(Play::Wave1, this));

	}

	void Play::ShowWaveAnimation(unsigned char wave)
	{
		m_Waves->UpdateText("Wave " + tostring(wave));

		Timer* hideText = new Timer(2000, false, [=]() {
			m_Waves->UpdateText("");
		});
	}

	void Play::Wave1()
	{
		ShowWaveAnimation(1);

		for (int pawnCount = 0; pawnCount < 100; pawnCount++)
		{
			TimelineExecuteEvent* pawnCreate = new TimelineExecuteEvent(m_PawnController, nullptr, 0.25f);
			std::function<void(int, int)> func = n2dMakeFuncArgs2(PawnController::CreatePawn, m_PawnController);
			pawnCreate->SetFunction(func, 1, pawnCount);
			
			Game::s_SceneManager->AddTimelineEvent("main", pawnCreate);
		
		}

		TimelineExecuteEvent* gotoWave2 = new TimelineExecuteEvent(this, n2dMakeFunc(Play::NoPawns, this), -1.f);
		std::function<void()> func = n2dMakeFunc(Play::Wave2, this);
		gotoWave2->SetFunction(func);
		
		Game::s_SceneManager->AddTimelineEvent("main", gotoWave2);

		// Kamikazes
		for (int kCount = 0; kCount < 100; kCount++)
		{
			TimelineExecuteEvent* kamikazeCreate = new TimelineExecuteEvent(m_KamikazeController, nullptr, 6.f);
			std::function<void(int, int)> func = n2dMakeFuncArgs2(KamikazeController::CreateKamikaze,
				m_KamikazeController);
			kamikazeCreate->SetFunction(func, 1, kCount);

			Game::s_SceneManager->AddTimelineEvent("kamikazes", kamikazeCreate);
		}


		Game::s_SceneManager->StartAndResetTimeline("main");
		Game::s_SceneManager->StartAndResetTimeline("kamikazes");
	}

	void Play::Wave2()
	{
		Game::s_SceneManager->CleanTimeline("main");
		Game::s_SceneManager->CleanTimeline("kamikazes");
		ShowWaveAnimation(2);
	}

	bool Play::NoPawns()
	{
		if (m_PawnController)
		{
			return m_PawnController->PawnCount() == 0;
		}

		return false;
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