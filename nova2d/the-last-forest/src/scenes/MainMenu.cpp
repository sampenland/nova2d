#include "MainMenu.h"
#include "core/Game.h"

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
			m_Title = new Text("font1", "The Last Forest", "white",
				Rect(Game::s_Width / 2 - 150, Game::s_Height/2 - 25, 300, 50), 0);

			n2dAssetsLoadAndAddTexture("grass", "res/grassTile.png");
			n2dAssetsLoadAndAddTexture("trees", "res/treesTile.png");
			n2dAssetsLoadAndAddTexture("tree", "res/treeTile.png");
			n2dAssetsLoadAndAddTexture("player", "res/player.png");
			n2dAssetsLoadAndAddTexture("human", "res/human.png");
			n2dAssetsLoadAndAddTexture("water", "res/water.png");
			n2dAssetsLoadAndAddTexture("highlight", "res/highlightTile.png");
			n2dAssetsLoadAndAddTexture("deadtrees", "res/deadTrees.png");

			m_Instruction = new Text("font1", "space to start", "light-blue",
				Rect(Game::s_Width / 2 - 75, Game::s_Height / 2 + 100 - 25, 150, 25), 0);

			auto f = new auto ([=]() {
				m_Instruction->ToggleVisible();
			});

			m_Blinker = new Timer(1000, true, *f);

		}

		void MainMenu::Update()
		{
			if (n2dIsKeyDown(SDLK_SPACE))
			{
				n2dSceneChange("LevelOne");
				m_Blinker->DestroySelf();
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