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

			Vec2Int m_FrameSize;
			
		public:

			Image(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

			void SwapTexture(const std::string& assetName);

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }

			void SetScale(float scale);
			float GetScale() { return GetDrawScale(); }

			void OriginCenter() { GetDrawable()->OriginCenter(); }
			void OriginTopLeft() { GetDrawable()->OriginTopLeft(); }

			float OffsetX() { return GetDrawable()->OffsetX(); }
			float OffsetY() { return GetDrawable()->OffsetY(); }

			bool operator==(const Image& other);

			void Draw(float oX = 0.f, float oY = 0.f, float scale = 1.f) override;

			void DestroySelf() override;

		};
	}
}