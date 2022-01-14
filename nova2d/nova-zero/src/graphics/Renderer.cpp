#include "Renderer.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		DrawLayers* Renderer::s_DrawLayers;

		Renderer::Renderer(SDL_Window& window, const Color bkgColor)
		{
			m_Renderer = SDL_CreateRenderer(&window, -1, 0);
			m_BackgroundColor = bkgColor;
			s_DrawLayers = new DrawLayers();
		}

		Renderer::~Renderer()
		{
			if (m_Renderer)
				SDL_DestroyRenderer(m_Renderer);

			if (s_DrawLayers)
				delete s_DrawLayers;
		}

		void Renderer::PreDraw() const
		{
			SDL_SetRenderDrawColor(m_Renderer, (Uint8)m_BackgroundColor.r, (Uint8)m_BackgroundColor.g,
				(Uint8)m_BackgroundColor.b, (Uint8)m_BackgroundColor.a);
			SDL_RenderClear(m_Renderer);
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
	}
}