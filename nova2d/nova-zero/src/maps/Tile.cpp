#include "Tile.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maps
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		Tile::Tile(TiledMap* tilemap, Vec2Int tileSize, Vec2Int tilemapPosition, unsigned int tileGID, char layer)
			: Deleteable("tile_"), Drawable(tileSize)
		{
			m_TileGID = tileGID;

			m_Layer = layer;
			m_ID = n2dGameGetID();
			m_DeleteName = "tile_" + tostring(m_ID);

			m_TiledMap = tilemap;

			// Draw setup
			m_SrcRect.x = tilemapPosition.x;
			m_SrcRect.y = tilemapPosition.y;

			m_SrcRect.w = tileSize.x;
			m_SrcRect.h = tileSize.y;

			m_DestRect.w = tileSize.x;
			m_DestRect.h = tileSize.y;
		}

		void Tile::Draw(float oX, float oY)
		{
			if (!IsVisible()) return;

			m_DestRect.x = oX;
			m_DestRect.y = oY;

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), &m_TiledMap->GetTilemapTextureRef(), &m_SrcRect, &m_DestRect, m_Angle, NULL, m_Flip);

		}

		SDL_Rect* Tile::GetTilesetRect()
		{
			return &m_SrcRect;
		}

		void Tile::DestroySelf()
		{
			CleanUpdaters();

			SetDeleted(true);
		}
	}
}