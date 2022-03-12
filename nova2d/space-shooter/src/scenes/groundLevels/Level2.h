#pragma once
#include "core/Scene.h"
#include "maps/TiledMap.h"
#include "graphics/Image.h"
#include "../../GroundPlayer.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::maps;
	using namespace novazero::graphics;

	class Level2 :
		public Scene
	{

	private:

		TiledMap* m_Map = nullptr;

	public:

		Level2(const std::string& sceneName)
			: Scene(sceneName)
		{

		};

		void Update() override
		{
			if (n2dIsKeyDown(SDLK_d))
			{
				CAMERA->MoveX(1);
			}

			if (n2dIsKeyDown(SDLK_a))
			{
				CAMERA->MoveX(-1);
			}

			if (n2dIsKeyDown(SDLK_w))
			{
				CAMERA->MoveY(-1);
			}

			if (n2dIsKeyDown(SDLK_s))
			{
				CAMERA->MoveY(1);
			}
		}

		void Start() override
		{
			// Maps
			n2dAssetsLoadAndAddMap("level2", "res/maps/level2/level2.json",
				"res/maps/level2/level2.png", "res/maps/level2/level2-tileset.json");

			GroundPlayer* player = new GroundPlayer(Game::GetCenterScreen(), Vec2Int(16, 16), 0);

			CAMERA->SetFollowTarget((Positional*)player);
						
		}

		void OnEscape()
		{
			
		}

		void End() override
		{
			
		}

	};
}