#pragma once
#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"
#include "graphics/Text.h"
#include "../scenes/Lvl1.h"

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

			title = new Text("font1", "SPACE SHOOTER", "white",
				Rect(Game::s_Width / 2 - 300, Game::s_Height / 4, 600, 60), 0);
			title->SetPositionPercents(50, 15);

			playerCount1 = new Text("font1", "Press 1 for one Player", "light-blue",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 2 + 50, 400, 40), 0);
			playerCount1->SetPositionPercents(50, 40);

			playerCount2 = new Text("font1", "Press 2 for one Player", "light-blue",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 2 + 50, 400, 40), 0);
			playerCount2->SetPositionPercents(50, 60);
			
			spaceToContinue = new Text("font1", "press escape to quit", "red",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2 + 50, 200, 20), 0);
			spaceToContinue->SetPositionPercents(50, 90);
		
			auto startListening = new auto([=] {
				StartListening();
			});

			Timer* t = new Timer(1000, false, *startListening);
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
			Game::EndGame(0);
		}

		void End() override
		{
			title->DestroySelf();
			spaceToContinue->DestroySelf();
			playerCount1->DestroySelf();
			playerCount2->DestroySelf();
		}

	};
}