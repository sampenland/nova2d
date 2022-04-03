#pragma once
#include "core/Scene.h"
#include "maps/TileMap.h"
#include "../../actors/Player.h"
#include "../AllScenes.h"
#include "../../controllers/HumanController.h"

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

			TileMap* m_Background = nullptr;
			HumanController* m_HumanController = nullptr;
			Player* m_Player = nullptr;

		public:

			LevelOne(const std::string& sceneName);

			void CreateWorld();
			void SetupLevel();
			void StartLevel();

			void Start() override;
			void Update() override;
			void End() override;

		};
	}
}