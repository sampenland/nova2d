#include "TiledMap.h"
#include "../core/Game.h"
#include <fstream>
#include "TiledMapLayer.h"
#include "../logging/logging.h"
#include "Tile.h"
#include "Tileset.h"

namespace novazero
{
	namespace maps
	{
		using namespace logging;

		TiledMap::TiledMap(std::string& tiledJSONexportFilePath, std::string tilesetImgPath, std::string tilesetPath)
			: Deleteable("tilemap_"), Drawable(Vec2Int(0,0))
		{
			m_ID = n2dGameGetID();
			m_Layer = TILEMAP_DRAW_LAYER;

			m_DeleteName = "tilemap_" + tostring(m_ID);
			m_TilesetTexture = n2dAssetsLoadAndAddTexture(m_DeleteName, tilesetImgPath);

			LoadMap(tiledJSONexportFilePath, tilesetPath);

			m_CleanID = n2dAddDeleteable(this);
			n2dAddDrawable(this, m_Layer);
		}

		void TiledMap::LoadMap(std::string& tiledJSONexportFilePath, std::string& tilesetJSONexportFilePath)
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
				ParseMap(tilesetJSONexportFilePath);
			}
			else
			{
				LOG(LVL_FATAL_ERROR, "Could not load json file for tilemap");
				return;
			}
		}

		void TiledMap::LoadTileset(std::string& tilesetJSONexportFilePath)
		{
			std::ifstream file(tilesetJSONexportFilePath);

			if (file.is_open())
			{
				std::string readIn;
				std::string line;
				while (std::getline(file, line))
				{
					readIn.append(line);
				}

				m_Tileset = new Tileset(json::parse(readIn));
			}
			else
			{
				LOG(LVL_FATAL_ERROR, "Could not load json file for tilemap");
				return;
			}
		}

		void TiledMap::ParseMap(std::string& tilesetJSONPath)
		{
			m_BackgroundColor = m_TileMap["backgroundcolor"];
			m_BackgroundColor.erase(std::remove(m_BackgroundColor.begin(), m_BackgroundColor.end(), '#'), m_BackgroundColor.end());
			n2dAddColor("background", m_BackgroundColor, 255);
			n2dSetBackgroundColor("background");

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

			m_WidthInTiles = m_TileMap["width"];
			m_HeightInTiles = m_TileMap["height"];

			SetSize(Vec2Int(m_WidthInTiles * m_TileSize.x, m_HeightInTiles * m_TileSize.y));

			LoadTileset(tilesetJSONPath);
			ParseLayers(m_TileMap["layers"]);

			for (size_t i = 0; i < m_Layers.size(); i++)
			{
				CreateLayerTiles((unsigned int) i);
			}

		}

		void TiledMap::CreateLayerTiles(unsigned int layer)
		{
			if (m_Tileset)
			{
				std::vector< std::string>& data = m_Layers[layer]->m_Data;

				int x = 0;
				int y = 0;

				int tilesetWidth = m_Tileset->m_ImageSize.x;
				int tilesetHeight = m_Tileset->m_ImageSize.y;

				int tileWidth = m_Tileset->m_TileSize.x;
				int tileHeight = m_Tileset->m_TileSize.y;

				int cols = tilesetWidth / tileWidth;
				int rows = tilesetHeight / tileHeight;

				unsigned tile_index = 0;
				for (int row = 0; row < rows; row++)
				{
					for (int col = 0; col < m_Tileset->m_Columns; col++)
					{
						x = col * tileWidth;
						y = row * tileHeight;

						//Read the GID in little-endian byte order:
						unsigned int global_tile_id = 
							std::stoi(data[tile_index]) |
							std::stoi(data[tile_index + 1]) << 8 |
							std::stoi(data[tile_index + 2]) << 16 |
							std::stoi(data[tile_index + 3]) << 24;

						tile_index += 4;

						// Read out the flags
						bool flipped_horizontally = (global_tile_id & FLIPPED_HORIZONTALLY_FLAG);
						bool flipped_vertically = (global_tile_id & FLIPPED_VERTICALLY_FLAG);
						bool flipped_diagonally = (global_tile_id & FLIPPED_DIAGONALLY_FLAG);
						bool rotated_hex120 = (global_tile_id & ROTATED_HEXAGONAL_120_FLAG);

						// Clear all four flags
						global_tile_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
							FLIPPED_VERTICALLY_FLAG |
							FLIPPED_DIAGONALLY_FLAG |
							ROTATED_HEXAGONAL_120_FLAG);

						Tile* tile = new Tile(this, Vec2Int(tileWidth, tileHeight), Vec2Int(x, y), global_tile_id, m_Layer);
						
						m_Tiles[global_tile_id] = tile;

					}
				}
			}
		}

		void TiledMap::Draw(float oX, float oY)
		{
			DrawTileLayers();
		}

		void TiledMap::DrawTileLayers()
		{
			bool failed = false;
			std::vector<TiledMapLayer*>::iterator it = m_Layers.begin();
			while (it != m_Layers.end() && !failed)
			{
				std::vector<std::string>& data = (*it)->m_Data;
				
				// LAYER DRAW
				for (size_t i = 0; i < m_WidthInTiles * m_HeightInTiles; i++)
				{
					int tileGID = std::stoi(data.at(i));

					int x = (i % m_WidthInTiles) * m_Tileset->m_TileSize.x;
					int y = (i / m_WidthInTiles) * m_Tileset->m_TileSize.y;

					if (m_Tiles.find(tileGID) == m_Tiles.end())
					{
						LOG(LVL_NFE, "Tile map draw failed");
						failed = true;
						break;
					}
					m_Tiles[tileGID]->Draw(x, y);
				}

				it++;
			}
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
				newLayer->m_Data.clear();
				for (auto it2 = layer["data"].begin(); it2 != layer["data"].end();++it2)
				{
					int tileVal = (*it2);
					newLayer->m_Data.push_back(tostring(tileVal));
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
			n2dRemoveDrawable(m_ID, m_Layer);
			n2dRemoveDeleteable(m_CleanID);
			SetDeleted(true);
		}
	}
}