#pragma once
#include <map>
#include <string>
#include "SDL_ttf.h"

namespace novazero
{
	namespace utils
	{
		class FontManager
		{

		private:

			std::map<std::string, TTF_Font*> m_Fonts;

		public:

			FontManager();
			~FontManager();

			void AddFont(std::string fontName, std::string fontPath, int fontSize);
			TTF_Font* GetFont(std::string fontName);
			void RemoveFont(std::string fontName);

		};
	}
}