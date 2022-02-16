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
			Color* m_BackgroundColor;

		public:

			Renderer(SDL_Window& window, Color* backgroundColor);
			~Renderer();

			inline SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

			void SetBlendMode(bool enableAlpha);
			
			void SetBackgroundColor(const std::string& colorName);
			void SetDrawColor(const std::string& colorName, Uint8 alphaOverride = 255);

			void PreDraw() const;
			void PostDraw() const;
			void Draw() const;

		public:

			static DrawLayers* s_DrawLayers;

		};
	}
}