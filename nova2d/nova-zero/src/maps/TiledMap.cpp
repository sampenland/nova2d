#include "TiledMap.h"
#include "../core/Game.h"
#include <fstream>
#include "TiledMapLayer.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace maps
	{
		using namespace logging;

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
				ParseMap();
			}
			else
			{
				LOG(LVL_FATAL_ERROR, "Could not load json file for tilemap");
				return;
			}
		}

		void TiledMap::ParseMap()
		{
			m_CompressionLevel = m_TileMap["compressionlevel"];
			m_Infinte = m_TileMap["infinite"];
			m_NextLayerID = m_TileMap["nextlayerid"];
			m_NextObjectID = m_TileMap["nextobjectid"];
			
			std::string orientation = m_TileMap["orientation"];
			if (orientation == "orthogonal")
			{
				m_Orientation = MapOrientations::Orthogonal;
			}
			else if (orientation == "isometric")
			{
				m_Orientation = MapOrientations::Isometric;
			}
			else if (orientation == "staggered")
			{
				m_Orientation = MapOrientations::Staggered;
			}
			else if (orientation == "hexagonal")
			{
				m_Orientation = MapOrientations::Hexagonal;
			}
			else
			{
				m_Orientation = MapOrientations::Orthogonal;
			}

			std::string renderOrder = m_TileMap["renderorder"];
			if (renderOrder == "right-down")
			{
				m_RenderOrder = RenderOrders::RightDown;
			}
			else if (renderOrder == "right-up")
			{
				m_RenderOrder = RenderOrders::RightUp;
			}
			else if (renderOrder == "left-down")
			{
				m_RenderOrder = RenderOrders::LeftDown;
			}
			else if (renderOrder == "left-up")
			{
				m_RenderOrder = RenderOrders::LeftUp;
			}
			else
			{
				m_RenderOrder = RenderOrders::RightDown;
			}

			m_TiledVersion = m_TileMap["tiledversion"];
			m_TileSize = Vec2Int(m_TileMap["tilewidth"], m_TileMap["tileheight"]);

			m_Type = m_TileMap["type"];
			m_Version = m_TileMap["version"];

			m_HeightInTiles = m_TileMap["height"];
			m_WidthInTiles = m_TileMap["width"];

			ParseLayers(m_TileMap["layers"]);

			// TODO: tilesets
			int i = 0;

		}

		void TiledMap::ParseLayers(json layers)
		{
			ClearLayers();

			for (auto it = layers.begin(); it != layers.end(); ++it)
			{
				auto layer = (*it);
				
				TiledMapLayer* newLayer = new TiledMapLayer();
				
				// Name
				newLayer->m_Name = layer["name"];
				newLayer->m_ID = layer["id"];
				newLayer->m_Alpha = layer["opacity"];

				std::string layerType = layer["type"];
				if (layerType == "tilelayer")
				{
					newLayer->m_Type = MapLayerTypes::TileLayer;
				}
				else if (layerType == "objectgroup")
				{
					newLayer->m_Type = MapLayerTypes::ObjectGroup;
				}
				else if (layerType == "imagelayer")
				{
					newLayer->m_Type = MapLayerTypes::ImageLayer;
				}
				else if (layerType == "group")
				{
					newLayer->m_Type = MapLayerTypes::Group;
				}
				else
				{
					newLayer->m_Type = MapLayerTypes::TileLayer;
				}

				newLayer->m_Position = Vec2Int(layer["x"], layer["y"]);
				newLayer->m_Visible = layer["visible"];

				newLayer->m_WidthInTiles = layer["width"];
				newLayer->m_HeightInTiles = layer["height"];

				// Tile data
				for (auto it2 = layer["data"].begin(); it2 != layer["data"].end(); ++it2)
				{
					auto tileVal = (*it2);
					newLayer->m_Data.push_back(tileVal);
				}

				m_Layers.push_back(newLayer);

			}

		}

		void TiledMap::ClearLayers()
		{
			std::vector<TiledMapLayer*>::iterator it = m_Layers.begin();
			while (it != m_Layers.end())
			{
				(*it)->DestroySelf();
				it = m_Layers.erase(it);
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