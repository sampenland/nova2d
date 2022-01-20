#pragma once
#include "Color.h"
#include "../graphics/DrawLayers.h"
#include "../utils/ColorManager.h"

namespace novazero
{
	namespace core
	{
		class Game;
	}

	namespace graphics
	{
		using namespace utils;

		class Renderer
		{

		private:

			SDL_Renderer* m_Renderer;
			Color m_BackgroundColor;

		public:

			Renderer(SDL_Window& window, Color backgroundColor);
			~Renderer();

			inline SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
			
			void SetBackgroundColor(std::string colorName);

			void PreDraw() const;
			void PostDraw() const;
			void Draw() const;

		public:

			static DrawLayers* s_DrawLayers;

		};
	}
}