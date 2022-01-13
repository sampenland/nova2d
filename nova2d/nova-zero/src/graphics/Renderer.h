#pragma once
#include "SDL.h"
#include "../graphics/Color.h"

namespace novazero
{
	namespace graphics
	{
		using namespace graphics;

		class Renderer
		{

		private:

			SDL_Renderer* m_Renderer;
			Color m_BackgroundColor;

		public:

			Renderer(SDL_Window& window, const Color bkgColor);
			~Renderer();

			inline SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
			
			void SetBackgroundColor(Color c)
			{
				m_BackgroundColor = c;
			}

			void Update();
			void Draw() const;

		public:


		};
	}
}