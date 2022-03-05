#pragma once
#include "SDL.h"
#include <map>
#include <string>
#include "../thirdparty/jsonparser/json.hpp"
#include "../maps/TiledMap.h"

namespace novazero
{
	namespace utils
	{
		using namespace nlohmann;
		using namespace maps;

		class AssetManager
		{

		private:

			std::map<std::string, SDL_Texture*> m_Textures = {};
			std::map<std::string, TiledMap*> m_Tilemaps = {};

		public:

			AssetManager();

			void LoadAndAddTexture(const std::string& name, std::string path);
			void RemoveTexture(const std::string& name);
			SDL_Texture* GetTexture(std::string name);

			void LoadAndAddMap(const std::string& name, std::string mapPath, const std::string& tilesetPath);
			void RemoveMap(const std::string& name);
			TiledMap* GetMap(const std::string name);
			
			void DestroySelf();

		};

	}
}