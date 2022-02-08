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

			TextInput(const std::string& fontName, const std::string& placeholderText, const std::string& textColorName, 
				const std::string& backgroundColorName, Rect drawRect,
				char layer);

			void Configure(bool startSelected, int maxChars);
			std::string GetText() { return m_DisplayText->GetText(); }

			void Update();
			void Select(bool isSelected, bool reset);
			void Draw(float oX = 0.f, float oY = 0.f) override;
			void DestroySelf();

		};
	}
}