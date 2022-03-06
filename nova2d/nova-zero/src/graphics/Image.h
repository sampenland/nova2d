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

			SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
			Vec2Int m_FrameSize;
			
		public:

			Image(const std::string& assetName, Vec2 position, Vec2Int size, char layer);

			void Flip(SDL_RendererFlip flip);

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }

			void SetScale(float scale);
			float GetScale() { return GetDrawScale(); }

			void OriginCenter() { GetDrawable()->OriginCenter(); }
			void OriginTopLeft() { GetDrawable()->OriginTopLeft(); }

			int OffsetX() { return GetDrawable()->OffsetX(); }
			int OffsetY() { return GetDrawable()->OffsetY(); }

			bool operator==(const Image& other);

			void Draw(float oX = 0.f, float oY = 0.f) override;

			void DestroySelf() override;

		};
	}
}