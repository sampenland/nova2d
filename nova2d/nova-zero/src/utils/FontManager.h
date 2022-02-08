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

			void AddFont(const std::string& fontName, const std::string& fontPath, int fontSize);
			TTF_Font* GetFont(const std::string& fontName);
			void RemoveFont(const std::string& fontName);

		};
	}
}