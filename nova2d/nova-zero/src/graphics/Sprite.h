#pragma once
#include "../core/Positional.h"
#include "SDL_image.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		
		class Sprite : public Positional
		{
			
		private:

			SDL_Texture* m_SpriteSheet = nullptr;

			SDL_Rect* m_SrcRect = nullptr;
			SDL_Rect* m_DestRect = nullptr;

		public:

			Sprite(float x, float y, const char* spriteSheet);
			~Sprite();

			void Update();
			void Draw() const;

		};
	}
}