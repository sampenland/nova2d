#include "Renderer.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		Renderer::Renderer(SDL_Window& window, const Vec4 bkgColor)
		{
			m_Renderer = SDL_CreateRenderer(&window, -1, 0);
			m_BackgroundColor = bkgColor;
		}

		Renderer::~Renderer()
		{
			if (m_Renderer)
				SDL_DestroyRenderer(m_Renderer);
		}

		void Renderer::Update()
		{
			SDL_SetRenderDrawColor(m_Renderer, (Uint8)m_BackgroundColor.x, (Uint8)m_BackgroundColor.y, 
				(Uint8)m_BackgroundColor.z, (Uint8)m_BackgroundColor.w);

			SDL_RenderClear(m_Renderer);
		}

		void Renderer::Draw() const
		{
			SDL_RenderPresent(m_Renderer);
		}
	}
}