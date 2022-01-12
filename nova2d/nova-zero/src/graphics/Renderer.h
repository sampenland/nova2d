#pragma once
#include "SDL.h"
#include "../maths/Vec4.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		class Renderer
		{

		private:

			SDL_Renderer* m_Renderer;
			Vec4 m_BackgroundColor;

		public:

			Renderer(SDL_Window& window, const Vec4 bkgColor);
			~Renderer();

			inline SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
			
			void Update();

		public:


		};
	}
}