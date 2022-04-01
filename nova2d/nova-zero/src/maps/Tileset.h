#pragma once
#include <string>
#include "../maths/Vec2Int.h"
#include "../thirdparty/jsonparser/json.hpp"
#include "TileCollider.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace maps
	{
		using namespace nlohmann;
		using namespace maths;
		using namespace logging;

		class Tileset
		{

		public:

			unsigned int m_FirstGID = 0;
			int m_Columns = 0;
			std::string m_Image = "";
			Vec2Int m_ImageSize = Vec2Int(0, 0);
			int m_Margin = 0;
			int m_Spacing = 0;
			std::string m_Name = "";
			int m_TileCount = 0;
			std::string m_TiledVersion = "";
			Vec2Int m_TileSize = Vec2Int(0, 0);
			std::string m_Version = "";
			const std::string m_Type = "tileset";

			std::vector<TileCollider*> m_Tiles;

			Tileset(json tileset, unsigned int firstGID);

			void LoadTileArray(json tiles);

		};
	}
}