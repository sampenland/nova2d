#include "Sprite.h"
#include "../utils/TextureLoader.h"
#include "../logging/Logging.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace utils;
		using namespace logging;

		Sprite::Sprite(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: m_ID(0), m_Layer(0), m_SrcRect(SDL_Rect()), m_DestRect(SDL_Rect())
		{
			m_X = (int)position.x;
			m_Y = (int)position.y;
			m_Angle = 0;
			m_Layer = layer;
			
			m_AssetName = assetName;
			m_SpriteSheet = Game::s_AssetManager->GetTexture(assetName);

			// Draw setup
			m_SrcRect.x = 0;
			m_SrcRect.y = 0;
			m_SrcRect.w = (int)size.x;
			m_SrcRect.h = (int)size.y;
			m_DestRect.w = (int)size.x;
			m_DestRect.h = (int)size.y;

			// Final
			m_ID = Game::s_IDCount;
			Game::s_IDCount++;
			Game::s_Renderer->s_DrawLayers->AddSprite(this, m_Layer);
		}

		Sprite::~Sprite()
		{
			if (m_SpriteSheet)
			{
				m_SpriteSheet = NULL;
			}
			
			Game::s_Renderer->s_DrawLayers->RemoveSprite(m_ID, m_Layer);
		}

		void Sprite::Update()
		{

		}

		void Sprite::Draw()
		{
			m_DestRect.x = m_X;
			m_DestRect.y = m_Y;

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, &m_SrcRect, &m_DestRect, m_Angle, NULL, SDL_FLIP_NONE);
		}

		bool Sprite::operator==(const Sprite& other)
		{
			return m_ID == other.m_ID;
		}
	}
}