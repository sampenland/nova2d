#include "Renderer.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		DrawLayers* Renderer::s_DrawLayers;

		Renderer::Renderer(SDL_Window& window, Color* backgroundColor)
		{
			m_Renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED);
			m_BackgroundColor = backgroundColor;
			s_DrawLayers = new DrawLayers();
		}

		void Renderer::SetBlendMode(bool enableAlpha)
		{
			if(enableAlpha)
				SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
			else
				SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);

		}

		void Renderer::PreDraw() const
		{
			SDL_SetRenderDrawColor(m_Renderer, (Uint8)m_BackgroundColor->r, (Uint8)m_BackgroundColor->g,
				(Uint8)m_BackgroundColor->b, (Uint8)m_BackgroundColor->a);

			SDL_RenderClear(m_Renderer);
		}

		void Renderer::SetBackgroundColor(const char* colorName)
		{
			m_BackgroundColor = n2dGetColor(colorName);
		}

		void Renderer::SetDrawColor(const char* colorName, Uint8 alphaOverride)
		{
			Color* c = n2dGetColor(colorName);
			if (alphaOverride != 255) c->a = alphaOverride;
			if (c)
			{
				SDL_SetRenderDrawColor(GetSDLRenderer(), c->r, c->g, c->b, c->a);
			}
		}

		void Renderer::PostDraw() const
		{
			SDL_RenderPresent(m_Renderer);
		}

		void Renderer::Draw() const
		{
			PreDraw();
			
			if (s_DrawLayers)
				s_DrawLayers->DrawAllLayers();
			
			PostDraw();
		}

		void Renderer::DestroySelf()
		{
			if (m_Renderer)
				SDL_DestroyRenderer(m_Renderer);

			if (s_DrawLayers)
			{
				s_DrawLayers->ClearSprites();
				delete s_DrawLayers; // POSSIBLE BUG
			}
		}
	}
}