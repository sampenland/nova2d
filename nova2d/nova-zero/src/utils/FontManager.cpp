#include "FontManager.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace utils
	{
		FontManager::FontManager()
		{
			AddFont("font1", "res/fonts/pixel1.ttf", 20);
			AddFont("font2", "res/fonts/pixel2.ttf", 20);
			AddFont("font3", "res/fonts/pixel3.ttf", 20);
			AddFont("font4", "res/fonts/pixel4.ttf", 20);
		}

		FontManager::~FontManager()
		{
			m_Fonts.clear();
		}

		void FontManager::AddFont(std::string fontName, std::string fontPath, int fontSize)
		{
			TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

			if (!font)
			{
				LOG("Failed to load font.");
				LOG(fontName);
				return;
			}

			m_Fonts[fontName] = font;
		}

		TTF_Font* FontManager::GetFont(std::string fontName)
		{
			if (m_Fonts.find(fontName) != m_Fonts.end())
			{
				return m_Fonts[fontName];
			}

			LOG(fontName);
			LOG("Could not find font in manager.");
			
			return nullptr;
		}

		void FontManager::RemoveFont(std::string fontName)
		{
			if (m_Fonts.find(fontName) != m_Fonts.end())
			{
				m_Fonts.erase(fontName);
			}
		}
	}
}