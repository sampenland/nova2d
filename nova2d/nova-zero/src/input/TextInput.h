#pragma once
#include <string>
#include "../maths/Rect.h"
#include "../graphics/Text.h"
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"
#include "Inputable.h"

namespace novazero
{
	namespace input
	{
		using namespace maths;
		using namespace graphics;

		class TextInput : public Drawable, public Deleteable, public Inputable
		{

		private:

			Text* m_DisplayText = nullptr;
			SDL_Rect* m_Background = nullptr;
			std::string m_BackgroundColor = "";
			int m_MaxChars = 100;

			bool m_Selected = false;

		public:

			TextInput(std::string fontName, std::string placeholderText, std::string textColorName, std::string backgroundColorName, Rect drawRect,
				char layer);
			~TextInput();

			void Configure(bool startSelected, int maxChars);

			void Update();
			void Select(bool isSelected, bool reset);
			void Draw() override;

		};
	}
}