#include "Text.h"
#include "../core/Game.h"

namespace novazero
{
	using namespace core;

	namespace graphics
	{
		Text::Text(std::string fontName, std::string text, std::string colorName, Rect drawRect, char layer)
		{
			m_Position.x = drawRect.x;
			m_Position.y = drawRect.y;
			m_Layer = layer;

			m_TextColor = colorName;
			m_FontName = fontName;
			m_DisplayText = text;

			m_DrawRect.x = drawRect.x;
			m_DrawRect.y = drawRect.y;
			m_DrawRect.w = drawRect.w;
			m_DrawRect.h = drawRect.h;				
			
			Construct();

		}

		Text::~Text()
		{
			if(m_Texture)
				SDL_DestroyTexture(m_Texture);
		}

		void Text::Construct()
		{
			TTF_Font* font = n2dFontGet(m_FontName);
			Color* novaColor = n2dGetColor(m_TextColor);
			SDL_Color sdlColor = { novaColor->r, novaColor->g, novaColor->b };
			SDL_Surface* surface = TTF_RenderText_Solid(font, m_DisplayText.c_str(), sdlColor);

			if (!surface)
			{
				LOG(m_DisplayText);
				LOG("Failed to construct Text");
				return;
			}

			m_Texture = SDL_CreateTextureFromSurface(Game::s_Renderer->GetSDLRenderer(), surface);

			if (!m_Texture)
			{
				LOG(m_DisplayText);
				LOG("Failed to construct Text");
				return;
			}

			m_Constructed = true;

			SDL_FreeSurface(surface);
		}

		void Text::Draw()
		{
			if (!m_Constructed) return;

			SDL_RenderCopy(Game::s_Renderer->GetSDLRenderer(), m_Texture, NULL, &m_DrawRect);
		}

	}
}