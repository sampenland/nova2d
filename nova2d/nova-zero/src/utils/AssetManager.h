#pragma once
#include "SDL.h"
#include <map>
#include <string>

namespace novazero
{
	namespace utils
	{

		class AssetManager
		{

		private:

			std::map<std::string, SDL_Texture*> m_Textures = {};

		public:

			AssetManager();
			~AssetManager();

			void LoadAndAddTexture(const std::string& name, std::string path);
			void RemoveTexture(const std::string& name);
			
			SDL_Texture* GetTexture(std::string name);

		};

	}
}