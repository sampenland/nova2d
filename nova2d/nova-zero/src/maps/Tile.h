#pragma once
#include "../core/Deleteable.h"
#include "../graphics/Drawable.h"
#include "SDL.h"
#include "TiledMap.h"
#include "../graphics/Text.h"

namespace novazero
{
	namespace maps
	{
		using namespace core;
		using namespace graphics;

		/*
			nova2d Tile
			Basic low cost drawable
			Does not draw itself, needs a TiledMap to draw
		*/
		class Tile : 
			public Deleteable,
			public Drawable
		{

		private:

			unsigned int m_TileGID = 0;
			TiledMap* m_TiledMap;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;
			Vec2Int m_TileSize;

		public:

			Tile(TiledMap* tilemap, Vec2Int tileSize, Vec2Int tilemapPosition, unsigned int tileID, char layer);

			void Draw(float oX = 0.f, float oY = 0.f) override;
			SDL_Rect* GetTilesetRect();

			void DestroySelf();
		};
	}
}