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

		public:

			Sprite(float x, float y, const char* spriteSheet);
			~Sprite();

			void Draw() const;

		};
	}
}