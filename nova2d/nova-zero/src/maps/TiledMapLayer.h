#pragma once
#include "../maths/Vec2Int.h"
#include <string>
#include <vector>

namespace novazero
{
	namespace maps
	{
		using namespace maths;

		enum class DrawOrders
		{
			TopDown,
			Index
		};

		enum class TiledLayerEncoding
		{
			CSV,
			BASE64
		};

		enum class MapLayerTypes
		{
			TileLayer,
			ObjectGroup,
			ImageLayer,
			Group
		};

		struct MapProperty;

		class TiledMapLayer
		{

		public:

			unsigned int m_ID = 0;

			std::vector<std::string> m_Data;
			DrawOrders m_DrawOrder = DrawOrders::TopDown;
			TiledLayerEncoding m_Encoding = TiledLayerEncoding::CSV;

			int m_HeightInTiles = 0;
			int m_WidthInTiles = 0;

			std::string m_Image = "";
			bool m_Locked = false;
			std::string m_Name = "";

			// TODO: objects array

			double m_OffsetX = 0.00;
			double m_OffsetY = 0.00;
			double m_Alpha = 1.00;
			double m_ParallaxX = 0.00;
			double m_ParallaxY = 0.00;

			std::vector<MapProperty> m_Properties;
			std::vector<TiledMapLayer*> m_Layers;

			bool m_RepeatX = false;
			bool m_RepeatY = false;

			Vec2Int m_StartPosition = Vec2Int(0, 0);

			std::string m_TintColor = "";
			std::string m_TransparentColor = "";

			MapLayerTypes m_Type = MapLayerTypes::TileLayer;
			bool m_Visible = true;

			Vec2Int m_Position = Vec2Int(0, 0);
			
			// NOT SUPPORTED
			// --------------
			// Array of chunks
			// Compression
			// --------------

			TiledMapLayer() {};

			void DestroySelf() {};
		};
	}
}