#include "LevelOne.h"
#include "core/Game.h"
#include "utils/timeline/events/TimelineExecuteEvent.h"
#include "../../pickups/Water.h"
#include "../../pickups/Tree.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::maps;
		using namespace novazero::utils::timeline::events;

		LevelOne::LevelOne(const std::string& sceneName)
			: Scene(sceneName)
		{

		}

		void LevelOne::LoadResources()
		{
			n2dAssetsLoadAndAddTexture("grass", "res/grassTile.png");
			n2dAssetsLoadAndAddTexture("trees", "res/treesTile.png");
			n2dAssetsLoadAndAddTexture("tree", "res/treeTile.png");
			n2dAssetsLoadAndAddTexture("player", "res/player.png");
			n2dAssetsLoadAndAddTexture("human", "res/human.png");
			n2dAssetsLoadAndAddTexture("water", "res/water.png");
			n2dAssetsLoadAndAddTexture("highlight", "res/highlightTile.png");

			using namespace pickups;
			Water* w = new Water(3);
			Tree* t = new Tree(3);
		}

		void LevelOne::CreateWorld()
		{
			m_Background = new TileMap(Vec2Int(1280, 800), 9, 9);
			m_Background->CreateTextureFromOneTile("grass", Vec2Int(142, 88));

			const int treesY = Game::s_Height - 88;
			int treesX = 0;
			for (int i = 1; i < 8; i++)
			{
				treesX = 1 + (142 * i);
				Trees* tree = new Trees("trees", Vec2(treesX, treesY), Vec2Int(142, 88), 10);				

				if (AllScenes::s_Trees[i - 1])
				{
					AllScenes::s_Trees[i - 1]->DestroySelf();
				}
				AllScenes::s_Trees[i - 1] = tree;
			}

			m_Player = new Player("player", Vec2(Game::s_Width/2 - 71/2, Game::s_Height - 88*2), 
				Vec2Int(71, 70), 0);
		}

		void LevelOne::SetupLevel()
		{
			m_HumanController = new HumanController();

			// Create a list of events, creating the level
			TimelineExecuteEvent* h1 = new TimelineExecuteEvent(
				m_HumanController, nullptr, 1.f);

			std::function<void(int)> createFunc = n2dMakeFuncArgs1(HumanController::CreateHuman, 
				m_HumanController);

			h1->SetFunction(createFunc, 2);

			n2dAddTimeline("humans", h1);

		}

		void LevelOne::StartLevel()
		{
			// Start level
			n2dStartTimeline("humans");
		}

		void LevelOne::Start()
		{
			LoadResources();
			CreateWorld();
			SetupLevel();
			StartLevel();
		}

		void LevelOne::Update()
		{

		}

		void LevelOne::End()
		{
			n2dAssetsRemoveTexture("grassTile");
		}
	}

}