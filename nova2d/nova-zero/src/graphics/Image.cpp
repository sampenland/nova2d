#include "Image.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		Image::Image(std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: Deleteable("image_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "image_" + tostring(m_ID);
			m_Layer = layer;

			m_AssetName = assetName;

			m_Angle = 0;
			m_Layer = layer;

			m_ImageTexture = Game::s_AssetManager->GetTexture(assetName);
			m_FrameSize = size;

			// Draw setup
			m_SrcRect.x = 0;
			m_SrcRect.y = 0;
			m_SrcRect.w = (int)size.x;
			m_SrcRect.h = (int)size.y;
			m_DestRect.w = (int)size.x;
			m_DestRect.h = (int)size.y;

			LinkPositionalSprite(this);

			n2dAddDrawable(this, layer);
		}

		void Image::Flip(SDL_RendererFlip flip)
		{
			m_Flip = flip;
		}

		void Image::Scale(float scale)
		{
			m_Scale = scale;
			m_DestRect.w = m_FrameSize.x * scale;
			m_DestRect.h = m_FrameSize.y * scale;
		}

		void Image::Draw(float oX = 0.f, float oY = 0.f)
		{
			if (!m_Visible) return;

			m_SrcRect.x = 0;
			m_SrcRect.w = m_FrameSize.x;

			m_DestRect.x = (int)(m_Position.x + oX);
			m_DestRect.y = (int)(m_Position.y + oY);

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, &m_SrcRect, &m_DestRect, m_Angle, NULL, m_Flip);

		}

		bool Image::operator==(const Image& other)
		{
			return m_ID == other.m_ID;
		}

		void Image::DestroySelf()
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			SetDeleted(true);
		}
	}
}