#include "LevelOne.h"
#include "core/Game.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::maps;

		LevelOne::LevelOne(const std::string& sceneName)
			: Scene(sceneName)
		{

		}

		void LevelOne::LoadResources()
		{
			n2dAssetsLoadAndAddTexture("grassTile", "res/grassTile.png");
			n2dAssetsLoadAndAddTexture("player", "res/player.png");
		}

		void LevelOne::CreateWorld()
		{
			m_Background = new TileMap(Vec2Int(1280, 800), 9, 9);
			m_Background->CreateTextureFromOneTile("grassTile", Vec2Int(142, 88));

			m_Player = new Player("player", Vec2(Game::s_Width/2 - 71/2, Game::s_Height - 88*2), 
				Vec2Int(71, 70), 0);
		}

		void LevelOne::Start()
		{
			LoadResources();
			CreateWorld();
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