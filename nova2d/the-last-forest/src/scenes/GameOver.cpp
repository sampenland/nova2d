#include "GameOver.h"
#include "core/Game.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::core;

		GameOver::GameOver(const std::string& sceneName)
			:Scene(sceneName)
		{

		}

		void GameOver::Start()
		{
			m_Title = new Text("font1", "The forest is gone...", "white",
				Rect(0, 0, 500, 150), 10);
			m_Title->SetPositionPercents(50, 30);

			m_Instruction = new Text("font1", "space to reset", "white",
				Rect(0, 0, 400, 100), 10);
			m_Instruction->SetPositionPercents(50, 60);

			m_Blinker = new Timer(1000, true, [=]() {
				m_Title->ToggleVisible();
			});

			m_ReadyToExit = false;
			Timer* t = new Timer(1500, false, [=]() {
				m_ReadyToExit = true;
			});
		}

		void GameOver::Update()
		{
			if (n2dIsKeyDown(SDLK_SPACE) && m_ReadyToExit)
			{
				n2dSceneChange("MainMenu");

				m_Blinker->DestroySelf();
				m_Title->DestroySelf();
				m_Instruction->DestroySelf();
			}
		}

		void GameOver::End()
		{
			m_Title->DestroySelf();
			m_Instruction->DestroySelf();
			m_Blinker->DestroySelf();
		}

		void GameOver::DestroySelf()
		{

		}
	}
}