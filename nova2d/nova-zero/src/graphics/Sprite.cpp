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

		Sprite::Sprite(Vec2 position, const char* spriteSheet, Vec2 size)
			: m_ID(0), m_Layer(0)
		{
			if (!Game::s_Renderer->GetSDLRenderer())
			{
				LOG(spriteSheet);
				LOG("No game initialized before creation of Sprite");
				return;
			}

			m_X = (int)position.x;
			m_Y = (int)position.y;
			m_Angle = 0;

			m_SpriteSheet = TextureLoader::Load(spriteSheet);

			if (!m_SpriteSheet)
			{
				LOG(spriteSheet);
				LOG("Failed to create sprite");
				return;
			}

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
		}

		Sprite::~Sprite()
		{

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