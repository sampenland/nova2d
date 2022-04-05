#include "LevelOne.h"
#include "core/Game.h"
#include "../../pickups/Water.h"
#include "../../pickups/Tree.h"
#include "../../GameDesigner.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::maps;

		float LevelOne::s_MinHumanTime = 2000.f;
		float LevelOne::s_MaxHumanTime = 12000.f;

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
				Placement* tree = new Placement(GridTypes::PTree, g_PTreeHealth, gridPos, Vec2Int(142, 88), 10);
				tree->SetVisibleStats(false, false, true);
				tree->SetEnableStats(false, false);
				AllScenes::SetPlacementAt(tree, gridPos);
			}

			m_Player = new Player("player", Vec2(Game::s_Width / 2 - 71 / 2, Game::s_Height - 88 * 2.5f),
				Vec2Int(71, 70), 0);

			m_HumanController = new HumanController();
			m_TreeController = new TreeController();
			m_ResourceController = new ResourceController();
		}

		void LevelOne::SetupLevel()
		{
			SetupHumans();
			SetupTrees();
			SetupResources();
		}

		void LevelOne::SetupHumans()
		{
			auto f = n2dMakeFunc(HumanController::CreateHuman, m_HumanController);
			Timer* humanSpawner = new Timer(&LevelOne::s_MinHumanTime, &LevelOne::s_MaxHumanTime, f);
		}

		void LevelOne::SetupTrees()
		{
			auto f = n2dMakeFunc(TreeController::CreateTree, m_TreeController);
			Timer* treeSpawner = new Timer(1000.f, true, f, g_MinTreeTime, g_MaxTreeTime);
		}

		void LevelOne::SetupResources()
		{
			auto f = n2dMakeFunc(ResourceController::CreateResource, m_ResourceController);
			Timer* resourceSpawner = new Timer(1000.f, true, f, g_MinResourceTime, g_MaxResourceTime);
		}

		void LevelOne::Start()
		{
			m_TimeSurvived = 0;
			//n2dAudioLoop(true, "music");

			CreateWorld();
			SetupLevel();

			m_TimeTicker = new Timer(1000, true, [=]() {
				m_TimeSurvived++;
			});

			m_TimeLived = new Text("font1", "lived: 0 seconds", "purple",
				Rect(0, 0, 200, 50), 30);
			m_TimeLived->SetPositionPercents(90, 5);
		
			m_Difficulty = new Timer(g_SpeedUpTime, true, [=]() {
				LevelOne::s_MaxHumanTime -= 1000;
				if (s_MaxHumanTime < 3.f)s_MaxHumanTime = 3.f;
			});
		}

		void LevelOne::Update()
		{
			m_TimeLived->UpdateText("lived: " + tostring(m_TimeSurvived) + " sec.");

			if (AllScenes::GetPTreesLeft() < 6)
			{
				m_HumanController->m_StartAttacks = 2;
			}
			else if (AllScenes::GetPTreesLeft() < 4)
			{
				m_HumanController->m_StartAttacks = 3;
			}
			else if (AllScenes::GetPTreesLeft() < 2)
			{
				m_HumanController->m_StartAttacks = 4;
			}
			else
			{
				m_HumanController->m_StartAttacks = 1;
			}

			if (n2dIsKeyDown(SDLK_ESCAPE))
			{
				n2dSceneChange("MainMenu");
				return;
			}

			CheckGameOver();
		}

		void LevelOne::CheckGameOver()
		{
			bool endGame = true;
			for (int i = 72; i < 79; i++)
			{
				if (AllScenes::s_Placements[i])
				{
					if (AllScenes::s_Placements[i]->GetType() == GridTypes::PTree)
					{
						endGame = false;
						break;
					}
				}
			}

			if (endGame)
			{
				n2dSceneChange("GameOver");
			}
		}

		void LevelOne::End()
		{
			m_Background->DestroySelf();
		}
	}

}