#pragma once
#include <string>
#include "../thirdparty/jsonparser/json.hpp"
#include "../core/Deleteable.h"

namespace novazero
{
	namespace maps
	{
		using namespace nlohmann;
		using namespace core;

		class TiledMap : Deleteable
		{
		
		private:
		
			unsigned int m_ID = 0;
			unsigned int m_CleanID = 0;

			std::string m_TilesetName = "";
			json m_TileMap;

		public:
		
			TiledMap(std::string& tiledJSONexportFilePath, std::string tilesetName);

			void LoadMap(std::string& tiledJSONexportFilePath);

			void DestroySelf();

		};
	}
}