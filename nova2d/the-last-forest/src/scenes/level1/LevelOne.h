#pragma once
#include "core/Scene.h"
#include "maps/TileMap.h"
#include "../../actors/Player.h"
#include "../AllScenes.h"
#include "../../controllers/HumanController.h"
#include "../../controllers/TreeController.h"
#include "../../controllers/ResourceController.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::core;
		using namespace novazero::maps;
		using namespace actors;
		using namespace controllers;

		class LevelOne :
			public Scene
		{

		private:

			Uint64 m_TimeSurvived = 0;
			Timer* m_TimeTicker = nullptr;

			TileMap* m_Background = nullptr;
			ResourceController* m_ResourceController = nullptr;
			Player* m_Player = nullptr;

			Text* m_TimeLived = nullptr;
			Timer* m_Difficulty = nullptr;

		public:

			HumanController* m_HumanController = nullptr;
			TreeController* m_TreeController = nullptr;

		public:

			LevelOne(const std::string& sceneName);

			void CreateWorld();
			void SetupLevel();
			void CheckGameOver();

			void SetupHumans();
			void SetupTrees();
			void SetupResources();

			void Start() override;
			void Update() override;
			void End() override;

			static float s_MinHumanTime;
			static float s_MaxHumanTime;

		};
	}
}