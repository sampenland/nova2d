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

			SDL_Rect* m_SrcRect = nullptr;
			SDL_Rect* m_DestRect = nullptr;

			Vec2 m_Position;

		public:

			Sprite(Vec2 position, const char* spriteSheet);
			~Sprite();

			void Update();
			void Draw() const;

			bool operator==(const Sprite& other);

		public:

			unsigned int m_ID;

		};
	}
}