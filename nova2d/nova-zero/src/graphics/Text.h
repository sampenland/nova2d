#pragma once
#include <string>
#include "../graphics/Color.h"
#include "../maths/Rect.h"
#include "../core/Positional.h"
#include "../graphics/Drawable.h"
#include "SDL.h"

namespace novazero
{
	using namespace maths;
	using namespace core;

	namespace graphics
	{
		class Text : public Positional, public Drawable
		{

		private:

			SDL_Texture* m_Texture = nullptr;
			std::string m_DisplayText = "";
			std::string m_TextColor;
			SDL_Rect m_DrawRect;
			std::string m_FontName;
			bool m_Constructed = false;

		public:

			Text(std::string fontName, std::string text, std::string colorName, Rect drawRect, char layer);
			~Text();

			void Construct();

			void Draw() override;

		};
	}
}