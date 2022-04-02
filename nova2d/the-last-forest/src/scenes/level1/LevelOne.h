#pragma once
#include "core/Scene.h"
#include "maps/TileMap.h"
#include "../../actors/Player.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::core;
		using namespace novazero::maps;
		using namespace actors;

		class LevelOne :
			public Scene
		{

		private:

			TileMap* m_Background = nullptr;
			
			Player* m_Player = nullptr;

		public:

			LevelOne(const std::string& sceneName);

			void LoadResources();
			void CreateWorld();

			void Start() override;
			void Update() override;
			void End() override;

		};
	}
}