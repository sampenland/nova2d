#pragma once
#include "../graphics/Sprite.h"
#include "../core/EventListener.h"
#include "../maths/Vec2.h"
#include "../utils/TextureLoader.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		class SimpleUDLRController :
			public EventListener
		{

		private:

			Sprite* m_Sprite = nullptr;

		public:

			SimpleUDLRController(const char* spriteSheet, Vec2 position, Vec2 size, char layer);
			~SimpleUDLRController();

			void Update() override;

		};
	}
}