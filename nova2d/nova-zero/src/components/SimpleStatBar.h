#pragma once
#include "../core/Positional.h"
#include "../maths/Rect.h"
#include "../graphics/Drawable.h"
#include "../graphics/Color.h"
#include "SDL.h"
#include "../core/Deleteable.h"

namespace novazero
{
	using namespace core;
	using namespace maths;
	using namespace graphics;

	namespace components
	{
		class SimpleStatBar
			: public Drawable, public Deleteable
		{

		private:

			bool m_IsVertical = true;

			SDL_Rect* m_Foreground;
			SDL_Rect* m_Outline;
			SDL_Rect* m_Background;
			float m_Scale = 1.f;

			std::string m_OutlineColor;
			std::string m_BackgroundColor;
			std::string m_ForegroundColor;
			std::string m_ForegroundColorAll;
			std::string m_ForegroundColorHalf;
			std::string m_ForegroundColorFourth;

			Vec2Int m_Pos;
			Vec2Int m_Size;

			int m_Value = 0;

			int m_OutlineThickness = 2;

		public:

			SimpleStatBar(bool vertical, int x, int y, int w, int h, const std::string& colorOutline,
				const std::string& colorBackground, const std::string& colorForeground, char layer);

			void ConfigureThickness(int outlineThickness);
			void ConfigureNonForeground(int outlineThickness, const std::string& colorOutline, const std::string& colorBackground);
			void ConfigureForeground(const std::string& colorForeground, const std::string& colorForeground2,
				const std::string& colorForeground4);

			void SetMaxWidth(int w);
			void Scale(float scale);

			void Update(int v, int x, int y);
			void Draw(float oX = 0.f, float oY = 0.f) override;

			void DestroySelf();

		};
	}
}