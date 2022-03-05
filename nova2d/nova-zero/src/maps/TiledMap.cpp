#include "TiledMap.h"
#include "../core/Game.h"
#include <fstream>

namespace novazero
{
	namespace maps
	{
		TiledMap::TiledMap(std::string& tiledJSONexportFilePath, std::string tilesetName)
			: Deleteable("tilemap_")
		{
			m_ID = n2dGameGetID();

			m_TilesetName = tilesetName;
			m_DeleteName = "tilemap_" + tostring(m_ID);

			LoadMap(tiledJSONexportFilePath);

			m_CleanID = n2dAddDeleteable(this);
		}

		void TiledMap::LoadMap(std::string& tiledJSONexportFilePath)
		{
			std::ifstream file(tiledJSONexportFilePath);

			if (file.is_open())
			{
				std::string readIn;
				std::string line;
				while (std::getline(file, line))
				{
					readIn.append(line);
				}

				m_TileMap = json::parse(readIn);
				
			}
			else
			{
				LOG(LVL_FATAL_ERROR, "Could not load json file for tilemap");
				return;
			}
		}

		void TiledMap::DestroySelf()
		{
			m_TileMap = NULL;
			n2dRemoveDeleteable(m_CleanID);
			SetDeleted(true);
		}
	}
}