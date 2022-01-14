#pragma once
#include "../core/Positional.h"
#include "SDL_image.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace maths;
		
		class Sprite : public Positional
		{
			
		private:

			SDL_Texture* m_SpriteSheet = nullptr;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;

			Vec2 m_Position;

		public:

			Sprite(Vec2 position, const char* spriteSheet, Vec2 size);
			~Sprite();

			void Update();
			void Draw();

			bool operator==(const Sprite& other);

		public:

			unsigned int m_ID;
			char m_Layer;

		};
	}
}