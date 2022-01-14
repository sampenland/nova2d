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

		Sprite::Sprite(Vec2 position, const char* spriteSheet)
		{
			if (!Game::s_Renderer->GetSDLRenderer())
			{
				LOG(spriteSheet);
				LOG("No game initialized before creation of Sprite");
				return;
			}

			m_X = position.x;
			m_Y = position.y;
			m_Angle = 0;

			m_SpriteSheet = TextureLoader::Load(spriteSheet);

			if (!m_SpriteSheet)
			{
				LOG(spriteSheet);
				LOG("Failed to create sprite");
				return;
			}



			m_ID = Game::s_IDCount;
			Game::s_IDCount++;
		}

		Sprite::~Sprite()
		{

		}

		void Sprite::Update()
		{

		}

		void Sprite::Draw() const
		{
			SDL_RenderCopy(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, NULL, NULL);
			
			//SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, 
			//	NULL, NULL, m_Angle, NULL, SDL_FLIP_NONE);
		}

		bool Sprite::operator==(const Sprite& other)
		{
			return m_ID == other.m_ID;
		}
	}
}