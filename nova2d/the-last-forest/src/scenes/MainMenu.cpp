#include "MainMenu.h"
#include "core/Game.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::core;

		MainMenu::MainMenu(const std::string& sceneName)
			: Scene(sceneName)
		{ }

		void MainMenu::Start()
		{
			AllScenes::NewGame();
			n2dAudioPlayOnce(false, "start");

			m_Title = new Text("font3", "The Last Forest stands strong but cannot survive........ us.", "white",
				Rect(0, 0, 800, 100), 0);
			m_Title->SetPositionPercents(50, 20);

			m_Instruction = new Text("font1", "space to start", "light-blue",
				Rect(0, 0, 200, 60), 0);
			m_Instruction->SetPositionPercents(50, 80);

			auto f = new auto ([=]() {
				m_Instruction->ToggleVisible();
			});

			m_Blinker = new Timer(1000, true, *f);

			m_Controls = new Text("narrow", "W  S  A  D    ::    Place Position", "white",
				Rect(0, 0, 300, 45), 2);
			m_Controls->SetPositionPercents(50, 40);

			m_Controls2 = new Text("narrow", "Up Down Right Left    ::    Move", "white",
				Rect(0, 0, 300, 45), 2);
			m_Controls2->SetPositionPercents(50, 50);

			m_Controls3 = new Text("font3", "space to place item", "white",
				Rect(0, 0, 300, 30), 2);
			m_Controls3->SetPositionPercents(50, 60);

			m_ReadyToExit = false;
			Timer* t = new Timer(1500, false, [=]() {
				m_ReadyToExit = true;
			});

		}

		void MainMenu::Update()
		{
			if (n2dIsKeyDown(SDLK_SPACE))
			{
				n2dSceneChange("LevelOne");

				m_Blinker->DestroySelf();
				m_Title->DestroySelf();
				m_Instruction->DestroySelf();
				m_Controls->DestroySelf();
				m_Controls2->DestroySelf();
				m_Controls3->DestroySelf();
			}

			if (m_ReadyToExit && n2dIsKeyDown(SDLK_ESCAPE))
			{
				Game::EndGame(0);
				return;
			}
		}

		void MainMenu::End()
		{
			
		}

		void MainMenu::DestroySelf()
		{

		}
	}
}