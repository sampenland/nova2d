#pragma once
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"

namespace novazero
{
	namespace maps
	{
		using namespace graphics;

		class TileMap :
			public Drawable,
			public Deleteable
		{

		private:

			unsigned int m_TileColumns;
			unsigned int m_TileRows;

			SDL_Texture* m_BackgroundTexture = nullptr;
			SDL_Rect m_BackgroundRect;
			Vec2Int m_TileSize;

		public:

			TileMap(Vec2Int size, unsigned int columns, unsigned int rows);

			void CreateTextureFromOneTile(const std::string& tileAssetName, Vec2Int tileSize);

			void Draw(float oX = 0.f, float oY = 0.f, float scale = 1.f) override;

			void DestroySelf();

		};
	}
}