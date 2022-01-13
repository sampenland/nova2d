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

		Sprite::Sprite(float x, float y, const char* spriteSheet)
		{
			if (!Game::s_Renderer->GetSDLRenderer())
			{
				LOG(spriteSheet);
				LOG("No game initialized before creation of Sprite");
				return;
			}

			m_X = x;
			m_Y = y;
			m_Angle = 0;

			m_SpriteSheet = TextureLoader::Load(spriteSheet);

			if (!m_SpriteSheet)
			{
				LOG(spriteSheet);
				LOG("Failed to create sprite");
				return;
			}
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
	}
}