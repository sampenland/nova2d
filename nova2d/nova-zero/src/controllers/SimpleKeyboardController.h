#pragma once
#include "../graphics/Sprite.h"
#include "../core/EventListener.h"
#include "../maths/Vec2.h"
#include "../utils/TextureLoader.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		class SimpleKeyboardController :
			public EventListener
		{

		private:

			Sprite* m_Sprite = nullptr;

		public:

			SimpleKeyboardController(const char* spriteSheet, Vec2 position);
			~SimpleKeyboardController();

			void Update() override;

		};
	}
}