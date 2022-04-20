#include "FontManager.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace utils
	{
		FontManager::FontManager()
		{
			if (TTF_Init() != 0) 
			{
				LOG(LVL_NON_FATAL_ERROR, "Could not start TTF library.", __FILE__, __LINE__);
				return;
			}

			AddFont("font1", "res/fonts/pixel1.ttf", 20);
			AddFont("font2", "res/fonts/pixel2.ttf", 20);
			AddFont("font3", "res/fonts/pixel3.ttf", 20);
			AddFont("font4", "res/fonts/pixel4.ttf", 20);
			AddFont("narrow", "res/fonts/narrow.ttf", 30);
		}

		FontManager::~FontManager()
		{
			m_Fonts.clear();
		}

		void FontManager::AddFont(const std::string& fontName, const std::string& fontPath, int fontSize)
		{
			TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

			if (!font)
			{
				LOG(LVL_NON_FATAL_ERROR, "Failed to load font: " + fontName, __FILE__, __LINE__);
				LOG(LVL_NON_FATAL_ERROR, TTF_GetError(), __FILE__, __LINE__);
				return;
			}

			m_Fonts[fontName] = font;
		}

		TTF_Font* FontManager::GetFont(const std::string& fontName)
		{
			if (m_Fonts.find(fontName) != m_Fonts.end())
			{
				return m_Fonts[fontName];
			}

			LOG(LVL_WARNING, "Could not find font in manager: " + fontName, __FILE__, __LINE__);
			
			return nullptr;
		}

		void FontManager::RemoveFont(const std::string& fontName)
		{
			if (m_Fonts.find(fontName) != m_Fonts.end())
			{
				m_Fonts.erase(fontName);
			}
		}
	}
}