#pragma once
#include <string>
#include "../core/Deleteable.h"
#include "SDL.h"
#include "Drawable.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		class Image : public Drawable, public Deleteable
		{

		private:

			std::string m_AssetName;
			SDL_Texture* m_ImageTexture;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;
			float m_Scale = 1.f;

			SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
			Vec2Int m_FrameSize;
			
		public:

			Image(std::string& assetName, Vec2 position, Vec2Int size, char layer);

			void Scale(float scale);
			float GetScale() { return m_Scale; }

			void Flip(SDL_RendererFlip flip);

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }

			bool operator==(const Image& other);

			void Draw(float oX = 0.f, float oY = 0.f) override;

			void DestroySelf() override;

		};
	}
}