#include "Tileset.h"

namespace novazero
{
	namespace maps
	{
		Tileset::Tileset(json tileset, unsigned int firstGID)
		{
			m_FirstGID = firstGID;

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

			LoadTileArray(tileset["tiles"]);

		}

		void Tileset::LoadTileArray(json tiles)
		{
			for (auto& el : tiles.items())
			{
				std::cout << " ---- " << std::endl;
				auto tile = el.value();
				unsigned int id = tile["id"];
				auto obj = tile["objectgroup"];
				unsigned int objID = obj["id"];

				auto shapes = obj["objects"];

				std::cout << el.value() << std::endl;
				for (auto& shape : shapes.items())
				{
					std::cout << shape.key() << " : " << shape.value() << std::endl;
				}

				std::cout << " ---- " << std::endl;
			}
		}
	}
}