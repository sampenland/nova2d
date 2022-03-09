#pragma once
#include "../core/Deleteable.h"
#include "../graphics/Drawable.h"
#include "SDL.h"
#include "TiledMap.h"

namespace novazero
{
	namespace maps
	{
		using namespace core;
		using namespace graphics;

		class Tile : 
			public Deleteable,
			public Drawable
		{

		private:

			TiledMap* m_TiledMap;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;
			Vec2Int m_TileSize;

		public:

			Tile(TiledMap* tilemap, Vec2Int tileSize, Vec2Int tilemapPosition, Vec2 position, char layer);

			void Draw(float oX = 0.f, float oY = 0.f) override;

			void DestroySelf();
		};
	}
}