#pragma once
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"
#include "../maths/Rect.h"

#include "SDL.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;
		using namespace core;
		using namespace maths;

		class DrawRect :
			public Drawable,
			public Deleteable
		{

		private:

			SDL_Rect* m_Fill;
			SDL_Rect* m_Outline;

			int m_CleanID = 0;
			bool m_Filled = false;
			std::string m_OutlineColor = "";
			std::string m_FillColor = "";

		public:

			DrawRect(std::string fillColor, std::string outlineColor,
				bool filled, Rect rect, int outlineThickness, char layer);

			void Draw() override;
			void DestroySelf();

		};
	}
}