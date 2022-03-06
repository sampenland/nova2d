#pragma once
#include <string>
#include <vector>
#include "../thirdparty/jsonparser/json.hpp"
#include "../core/Deleteable.h"
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace maps
	{
		using namespace nlohmann;
		using namespace core;
		using namespace maths;

		class TiledMapLayer;

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

		class TiledMap : Deleteable
		{
		
		private:
		
			unsigned int m_ID = 0;
			unsigned int m_CleanID = 0;

		private:

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
			
			int m_HeightInTiles = 0;
			int m_WidthInTiles = 0;

		private:

			std::string m_TilesetName = "";
			json m_TileMap;

		public:
		
			TiledMap(std::string& tiledJSONexportFilePath, std::string tilesetName);

			void LoadMap(std::string& tiledJSONexportFilePath);
			void ParseMap();

			void ParseLayers(json layers);
			void ClearLayers();

			void DestroySelf();

		};
	}
}