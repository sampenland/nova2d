#pragma once
#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"
#include "graphics/Text.h"
#include "../scenes/Lvl1.h"
#include "graphics/DrawableCollection.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::input;
	using namespace novazero::graphics;

	class MainMenu :
		public Scene
	{

	private:

		Text* title = nullptr;
		Text* spaceToContinue = nullptr;
		Text* playerCount1 = nullptr;
		Text* playerCount2 = nullptr;

		DrawableCollection* screen = nullptr;

	public:

		MainMenu(std::string sceneName)
			: Scene(sceneName)
		{
			
		};

		~MainMenu() { };

		void Update() override
		{

		}

		void Start() override
		{
			n2dScoreSet(0);
			Player::s_Player1Streak = 0;
			Player::s_Player1MaxStreak = 0;
			Player::s_Player2Streak = 0;
			Player::s_Player2MaxStreak = 0;

			screen = new DrawableCollection(Vec2(0, 0), 0);

			title = new Text("font1", "SPACE SHOOTER", "white",
				Rect(Game::s_Width / 2 - 300, Game::s_Height / 4, 600, 60), 0);
			title->SetPositionPercents(50, 15);
			title->SetDrawableCollection(screen);

			playerCount1 = new Text("font1", "Press 1 for one Player", "light-blue",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 2 + 50, 400, 40), 0);
			playerCount1->SetPositionPercents(50, 40);
			playerCount1->SetDrawableCollection(screen);

			playerCount2 = new Text("font1", "Press 2 for one Player", "light-blue",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 2 + 50, 400, 40), 0);
			playerCount2->SetPositionPercents(50, 60);
			playerCount2->SetDrawableCollection(screen);
			
			spaceToContinue = new Text("font1", "press escape to quit", "red",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2 + 50, 200, 20), 0);
			spaceToContinue->SetPositionPercents(50, 90);
			spaceToContinue->SetDrawableCollection(screen);


			const float crawlTime = 5000.0f;
			n2dTweenAddFloat(screen->GetYRef(), Game::s_Height, 0, crawlTime, false, true);
		
			auto startListening = new auto([=] {
				StartListening();
			});

			Timer* t = new Timer(crawlTime, false, *startListening);
		}

		void StartListening()
		{
			n2dAddKeyDownListener(SDLK_1, MainMenu::OnePlayer, this);
			n2dAddKeyDownListener(SDLK_2, MainMenu::TwoPlayer, this);
			n2dAddKeyDownListener(SDLK_ESCAPE, MainMenu::OnEscape, this);
		}

		void OnePlayer()
		{
			Lvl1::s_Players = 1;
			n2dRemoveKeyDownListener(SDLK_1);
			n2dRemoveKeyDownListener(SDLK_2);
			n2dRemoveKeyDownListener(SDLK_ESCAPE);
			n2dSceneChange("level1");
		}

		void TwoPlayer()
		{
			Lvl1::s_Players = 2;
			n2dRemoveKeyDownListener(SDLK_1);
			n2dRemoveKeyDownListener(SDLK_2);
			n2dRemoveKeyDownListener(SDLK_ESCAPE);
			n2dSceneChange("level1");
		}

		void OnEscape()
		{
			End();
			Game::EndGame(0);
		}

		void End() override
		{
			title->DestroySelf();
			spaceToContinue->DestroySelf();
			playerCount1->DestroySelf();
			playerCount2->DestroySelf();
			screen->DestroySelf();
		}

	};
}