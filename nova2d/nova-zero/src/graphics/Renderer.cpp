#include "Renderer.h"

namespace novazero
{
	namespace graphics
	{
		Renderer::Renderer(SDL_Window& window)
		{
			m_Renderer = SDL_CreateRenderer(&window, -1, 0);
		}

		Renderer::~Renderer()
		{
			if (m_Renderer)
				delete m_Renderer;
		}
	}
}