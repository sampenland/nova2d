#pragma once
#include "../graphics/Color.h"
#include "../graphics/Drawable.h"

namespace novazero
{
	namespace core
	{
		using namespace novazero::graphics;

		class Environment :
			public Drawable
		{

		private:

			Color* m_WorldLightingColor = nullptr;
			SDL_Rect m_WorldLight;

		public:

			Uint8* m_WorldLightingIntensity = nullptr;

		public:

			Environment(Uint8 intensity);

			void Draw(float oX = 1.f, float oY = 1.f, float scale = 1.f) override;

			void DestroySelf();

		};
	}
}