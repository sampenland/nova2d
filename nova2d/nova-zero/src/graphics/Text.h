#pragma once
#include <string>
#include "../graphics/Color.h"
#include "../maths/Rect.h"
#include "../core/Positional.h"
#include "../graphics/Drawable.h"
#include "SDL.h"
#include "../core/Referenceable.h"
#include "../core/Deleteable.h"

namespace novazero
{
	using namespace maths;
	using namespace core;

	namespace graphics
	{
		class Text : public Drawable, public Referenceable, public Deleteable
		{

		private:

			SDL_Texture* m_Texture = nullptr;
			std::string m_DisplayText = "";
			std::string m_TextColor;
			SDL_Rect m_DrawRect;
			std::string m_FontName;
			bool m_Constructed = false;
			bool m_Visible = true;
			int m_CharMax = 0;
			bool m_Dynamic = false;

		public:

			Text(std::string fontName, std::string text, std::string colorName, Rect drawRect, char layer, bool autoAddDrawable = true);
			~Text();

			void Construct(std::string newText, Vec2Int newPos);
			void UpdateText(std::string newText);
			void ManualAddDrawable(char layer);
			std::string GetText() { return m_DisplayText; }
			void SetDynamicWithCharMax(int max) { m_CharMax = max; m_Dynamic = true; }

			void Draw() override;
			void DestroySelf();

		};
	}
}