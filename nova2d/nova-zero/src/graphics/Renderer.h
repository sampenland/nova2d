#pragma once
#include "SDL.h"

namespace novazero
{
	namespace graphics
	{
		class Renderer
		{

		private:

			SDL_Renderer* m_Renderer = nullptr;

		public:

			Renderer(SDL_Window& window);
			~Renderer();

		};
	}
}