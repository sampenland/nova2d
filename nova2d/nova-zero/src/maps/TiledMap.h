#pragma once
#include <string>
#include <vector>
#include "../thirdparty/jsonparser/json.hpp"
#include "../core/Deleteable.h"
#include "../graphics/Drawable.h"
#include "../maths/Vec2Int.h"
#include "Tileset.h"
#include "SDL.h"

namespace novazero
{
	namespace maps
	{
		using namespace nlohmann;
		using namespace core;
		using namespace maths;

		class TiledMapLayer;
		class Tile;

		enum class MapOrientations
		{
			Orthogonal,
			Isometric,
			Staggered,
			Hexagonal
		};

		struct MapProperty
		{
			std::string Name;
			std::string Type;
			std::string PropertyType;
			std::string Value;
		};

		enum class RenderOrders
		{
			RightDown,
			RightUp,
			LeftDown,
			LeftUp
		};

		enum class Staggers
		{
			X,
			Y
		};

		enum class StaggerIndexs
		{
			ODD,
			EVEN
		};

		class TiledMap : Deleteable, public Drawable
		{
		
		private:
		
			unsigned int m_ID = 0;
			char m_Layer = 0;
			unsigned int m_CleanID = 0;

		private:

			SDL_Texture* m_TilesetTexture;
			Tileset* m_Tileset = nullptr;

			// Tiled Map Export vars
			std::string m_BackgroundColor;
			int m_CompressionLevel = -1;
			bool m_Infinte = false;
			int m_HexSideLength = 0;
			int m_NextLayerID = 0;
			int m_NextObjectID = 0;
			MapOrientations m_Orientation = MapOrientations::Orthogonal;
			double m_ParallaxOriginX = 0.00;
			double m_ParallaxOriginY = 0.00;
			RenderOrders m_RenderOrder = RenderOrders::RightDown;
			Staggers m_StaggerAxis = Staggers::X;
			StaggerIndexs m_StaggerIndex = StaggerIndexs::ODD;
			std::string m_TiledVersion;
			Vec2Int m_TileSize = Vec2Int(16, 16);
			std::string m_Type;
			std::string m_Version;

			std::vector<MapProperty> m_Properties;
			std::vector<TiledMapLayer*> m_Layers;

			std::vector<Tile*> m_Tiles;
			
			int m_HeightInTiles = 0;
			int m_WidthInTiles = 0;

		private:

			json m_TileMap;

		public:
		
			TiledMap(std::string& tiledJSONexportFilePath, std::string tilesetImgPath, std::string tilesetPath);

			SDL_Texture& GetTilemapTextureRef()
			{
				return *m_TilesetTexture;
			}

			void LoadMap(std::string& tiledJSONexportFilePath, std::string& tilesetJSONexportFilePath);
			void LoadTileset(std::string& tilesetJSONexportFilePath);
			void CreateTiles();
			void ParseMap(std::string& tilesetJSONPath);

			void ParseLayers(json layers);
			void ClearLayers();

			void Draw(float oX = 0.f, float oY = 0.f) override;
			void DrawTileLayers();

			void DestroySelf();

		};
	}
}