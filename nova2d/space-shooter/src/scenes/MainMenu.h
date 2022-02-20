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

		DrawableCollection* screen = nullptr;
		unsigned int crawlTweenId = 0;

	public:

		MainMenu(const std::string& sceneName)
			: Scene(sceneName)
		{
		};

		~MainMenu() { };

		void Update() override
		{
		}

		void Start() override
		{
			screen = new DrawableCollection(Vec2(0.f, (float)Game::s_Height), 0);

			title = new Text("font1", "SPACE SHOOTER", "white",
				Rect(Game::s_Width / 2 - 300, Game::s_Height / 4, 600, 60), 0);
			title->SetPositionPercents(50, 15);
			title->SetDrawableCollection(screen);

			playerCount1 = new Text("font1", "Press A to Begin", "light-blue",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 2 + 50, 400, 40), 0);
			playerCount1->SetPositionPercents(50, 40);
			playerCount1->SetDrawableCollection(screen);
			
			spaceToContinue = new Text("font1", "press home to quit", "red",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2 + 50, 200, 20), 0);
			spaceToContinue->SetPositionPercents(50, 90);
			spaceToContinue->SetDrawableCollection(screen);

			const float crawlTime = 5000.0f;
			crawlTweenId = n2dTweenAdd(false, screen->GetYRef(), (float)Game::s_Height, 0.f, crawlTime, false, true, TweenTypes::EaseOutBounce);
		
			auto startListening = new auto([=] {
				StartListening();
			});

			Timer* t = new Timer(crawlTime, false, *startListening);
			n2dAddKeyDownListener(SDLK_SPACE, MainMenu::WaitABit, this);
			n2dAddJoyKeyDownListener(0, SDL_CONTROLLER_BUTTON_A, MainMenu::WaitABit, this);
		}

		void WaitABit()
		{
			n2dRemoveKeyDownListener(SDLK_SPACE);
			n2dRemoveJoyKeyDownListener(0, SDL_CONTROLLER_BUTTON_A);
			n2dTweenRemove(crawlTweenId);
			screen->SetPosition(Vec2(0, 0));

			auto waitBeforeControlEnable = new auto([=] {
				StartListening();
			});

			Timer* t = new Timer(1000.f, false, *waitBeforeControlEnable);
		}

		void StartListening()
		{
			n2dAddKeyDownListener(SDLK_f, MainMenu::OnePlayer, this);
			n2dAddJoyKeyDownListener(0, SDL_CONTROLLER_BUTTON_A, MainMenu::OnePlayer, this);
			n2dAddKeyDownListener(SDLK_ESCAPE, MainMenu::OnEscape, this);
		}

		void OnePlayer()
		{
			n2dRemoveKeyDownListener(SDLK_f);
			n2dRemoveJoyKeyDownListener(0, SDL_CONTROLLER_BUTTON_A);
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
			screen->DestroySelf();
		}

	};
}