#include "Text.h"
#include "../core/Game.h"

namespace novazero
{
	using namespace core;

	namespace graphics
	{
		Text::Text(std::string fontName, std::string text, std::string colorName, Rect drawRect, char layer,
			bool autoAddDrawable) : Deleteable("text_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "text_" + std::to_string(m_ID);

			m_Position.x = (float)drawRect.x;
			m_Position.y = (float)drawRect.y;
			m_Layer = layer;

			m_TextColor = colorName;
			m_FontName = fontName;
			m_DisplayText = text;
			m_CharMax = text.length();

			SetSize(Vec2Int(drawRect.w, drawRect.h));

			m_DrawRect.x = drawRect.x;
			m_DrawRect.y = drawRect.y;
			m_DrawRect.w = drawRect.w;
			m_DrawRect.h = drawRect.h;	

			m_Dynamic = false;
			
			Construct(m_DisplayText, Vec2Int(drawRect.x, drawRect.y));

			if(autoAddDrawable) n2dAddDrawable(this, m_Layer);

		}

		void Text::ManualAddDrawable(char layer)
		{
			m_Layer = layer;
			n2dAddDrawable(this, m_Layer);
		}

		void Text::UpdateText(const std::string& newText)
		{
			Construct(newText, Vec2Int(m_DrawRect.x, m_DrawRect.y));
		}

		void Text::Construct(std::string newText, Vec2Int newPos)
		{
			TTF_Font* font = n2dFontGet(m_FontName);
			Color* novaColor = n2dGetColor(m_TextColor);
			SDL_Color sdlColor = { novaColor->r, novaColor->g, novaColor->b };
			
			if (m_Dynamic)
				m_DisplayText = newText.append(m_CharMax - newText.length(), ' ');
			else
				m_DisplayText = newText;

			SDL_Surface* surface = TTF_RenderText_Solid(font, m_DisplayText.c_str(), sdlColor);

			m_DrawRect.x = newPos.x;
			m_DrawRect.y = newPos.y;

			if (!surface)
			{
				m_Visible = false;
				return;
			}

			m_Visible = true;

			if(m_Texture)
				SDL_DestroyTexture(m_Texture);
			
			m_Texture = SDL_CreateTextureFromSurface(Game::s_Renderer->GetSDLRenderer(), surface);

			if (!m_Texture)
			{
				LOG(LVL_WARNING, "Failed to construct Text" + m_DisplayText);
				return;
			}

			m_Constructed = true;

			SDL_FreeSurface(surface);

		}

		void Text::Draw(float oX, float oY)
		{
			if (!m_Visible) return;
			if (!m_Constructed) return;

			m_DrawRect.x = (int)GetX() + oX;
			m_DrawRect.y = (int)GetY() + oY;

			SDL_RenderCopy(Game::s_Renderer->GetSDLRenderer(), m_Texture, NULL, &m_DrawRect);
		}

		void Text::DestroySelf()
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			CleanUpdaters();
			SetDeleted(true);
		}

	}
}