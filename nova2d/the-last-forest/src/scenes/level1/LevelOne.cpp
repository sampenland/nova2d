#include "LevelOne.h"
#include "core/Game.h"
#include "utils/timeline/events/TimelineExecuteEvent.h"
#include "../../pickups/Water.h"
#include "../../pickups/Tree.h"
#include "../../GameDesigner.h"

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

		void LevelOne::CreateWorld()
		{
			m_Background = new TileMap(Vec2Int(1280, 800), 9, 9);
			m_Background->CreateTextureFromOneTile("grass", Vec2Int(142, 88));

			const int treesY = Game::s_Height - 88;
			int treesX = 0;
			for (int i = 1; i < 8; i++)
			{
				treesX = 1 + (142 * i);

				int gridPos = 72 + i;
				Placement* tree = new Placement(GridTypes::PTree, 4, gridPos, Vec2Int(142, 88), 10);
				tree->SetVisibleStats(false, false, true);
				tree->SetEnableStats(false, false);
				AllScenes::SetPlacementAt(tree, gridPos);
			}

			m_Player = new Player("player", Vec2(Game::s_Width/2 - 71/2, Game::s_Height - 88*2), 
				Vec2Int(71, 70), 0);
		}

		void LevelOne::SetupLevel()
		{
			m_HumanController = new HumanController();

			TimelineExecuteEvent* execEvents = new TimelineExecuteEvent[g_LevelOneHumans];

			for (int i = 0; i < g_LevelOneHumans; i++)
			{
				// Create a list of events, creating the level
			
				float intervalTime = n2dRandomFloat(g_MinHumanTime, g_MaxHumanTime);

				TimelineExecuteEvent* tEvent = new TimelineExecuteEvent(
					m_HumanController, nullptr, intervalTime);

				std::function<void(int)> createFunc = n2dMakeFuncArgs1(HumanController::CreateHuman,
					m_HumanController);

				tEvent->SetFunction(createFunc, i);

				n2dAddTimeline("humans", tEvent);
			}
		}

		void LevelOne::StartLevel()
		{
			// Start level
			n2dStartTimeline("humans");
		}

		void LevelOne::Start()
		{
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