#include "TileMap.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maps
	{
		TileMap::TileMap(Vec2Int size, unsigned int columns, unsigned int rows)
			: Drawable(size), Deleteable("tilemap_"), m_TileColumns(columns), m_TileRows(rows)
		{

			m_ID = n2dGameGetID();
			m_Layer = TILEMAP_DRAW_LAYER;

			m_BackgroundRect.x = 0;
			m_BackgroundRect.y = 0;
			m_BackgroundRect.w = size.x;
			m_BackgroundRect.h = size.y;
		}

		void TileMap::CreateTextureFromOneTile(const std::string& tileAssetName, Vec2Int tileSize)
		{
			if (m_BackgroundTexture)
				SDL_DestroyTexture(m_BackgroundTexture);

			static bool onlyOnce = false;
			if (onlyOnce) return;
			onlyOnce = true;

			m_BackgroundTexture = SDL_CreateTexture(Game::s_Renderer->GetSDLRenderer(),
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1280, 800);

			SDL_SetTextureBlendMode(m_BackgroundTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Game::s_Renderer->GetSDLRenderer(), m_BackgroundTexture);

			SDL_Rect tileDestRect;
			tileDestRect.x = 0;
			tileDestRect.y = 0;
			tileDestRect.w = tileSize.x;   // tilesize
			tileDestRect.h = tileSize.y;  // tilesize

			m_BackgroundRect.x = 0;
			m_BackgroundRect.y = 0;
			m_BackgroundRect.w = 1280;
			m_BackgroundRect.h = 800;

			SDL_Texture* tile = n2dAssetsGetTexture(tileAssetName);

			int x = 0;
			int y = 0;
			const int xPadding = 1;
			const int yPadding = 4;

			for (unsigned int row = 0; row < m_TileRows; row++)
			{
				for (unsigned int col = 0; col < m_TileColumns; col++)
				{
					tileDestRect.x = xPadding + (col * tileSize.x);
					tileDestRect.y = yPadding + (row * tileSize.y);

					SDL_RenderCopy(Game::s_Renderer->GetSDLRenderer(), tile,
						NULL, &tileDestRect);
				}
			}

			SDL_SetRenderTarget(Game::s_Renderer->GetSDLRenderer(), NULL);

			n2dRemoveDrawable(m_ID, m_Layer);
			n2dAddDrawable(this, m_Layer);

		}

		void TileMap::Draw(float oX, float oY, float scale)
		{
			if (!IsVisible()) return;

			if (m_BackgroundTexture)
			{
				m_BackgroundRect.x = (int)oX;
				m_BackgroundRect.y = (int)oY;

				int w = m_BackgroundRect.w;
				int h = m_BackgroundRect.h;

				m_BackgroundRect.w = (int)(w * scale);
				m_BackgroundRect.h = (int)(h * scale);

				SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_BackgroundTexture, NULL, &m_BackgroundRect, m_Angle, NULL, m_Flip);

				m_BackgroundRect.w = w;
				m_BackgroundRect.h = h;
			}
		}

		void TileMap::DestroySelf()
		{

			if (m_BackgroundTexture)
				SDL_DestroyTexture(m_BackgroundTexture);

			n2dRemoveDrawable(m_ID, m_Layer);
			
			SetDeleted(true);
		}
	}
}