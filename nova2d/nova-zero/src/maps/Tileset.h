#pragma once
#include <string>
#include "../maths/Vec2Int.h"
#include "../thirdparty/jsonparser/json.hpp"

namespace novazero
{
	namespace maps
	{
		using namespace nlohmann;
		using namespace maths;

		class Tileset
		{

		public:

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

			Tileset(json tileset)
			{
				m_Columns = tileset["columns"];
				m_Image = tileset["image"];
				m_ImageSize = Vec2Int(tileset["imagewidth"], tileset["imageheight"]);
				m_Margin = tileset["margin"];
				m_Spacing = tileset["spacing"];
				m_Name = tileset["name"];
				m_TileCount = tileset["tilecount"];
				m_TileSize = Vec2Int(tileset["tilewidth"], tileset["tileheight"]);
				m_TiledVersion = tileset["tiledversion"];
				m_Version = tileset["version"];
			}
		};
	}
}