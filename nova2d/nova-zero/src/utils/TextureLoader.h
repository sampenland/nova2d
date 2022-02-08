#pragma once
#include "SDL.h"
#include <string>

namespace novazero
{
	namespace utils
	{
		class TextureLoader
		{
		public:
			static SDL_Texture* Load(const std::string& path);
		};
	}
}