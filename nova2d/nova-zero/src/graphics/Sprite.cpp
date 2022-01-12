#include "Sprite.h"
#include "../utils/TextureLoader.h"
#include "../logging/Logging.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace utils;
		using namespace logging;

		Sprite::Sprite(float x, float y, const char* spriteSheet)
		{
			this->SetX(x);
			this->SetY(y);
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

		void Sprite::Draw() const
		{

		}
	}
}