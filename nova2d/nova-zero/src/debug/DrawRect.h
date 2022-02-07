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
			int m_Thickness = 2;

		public:

			DrawRect(std::string fillColor, std::string outlineColor,
				bool filled, Rect rect, int outlineThickness, char layer);

			Vec2Int GetDrawRectSize() { return Vec2Int(m_Fill->w, m_Fill->h); }
			void SetDrawRectSize(Rect* rect) 
			{
				m_Outline->x = rect->x;
				m_Outline->y = rect->y;
				m_Outline->w = rect->w;
				m_Outline->h = rect->h;

				m_Fill->x = rect->x + m_Thickness;
				m_Fill->y = rect->y + m_Thickness;
				m_Fill->w = rect->w - 2 * m_Thickness;
				m_Fill->h = rect->h - 2 * m_Thickness;
			}

			void Draw(float oX = 0.f, float oY = 0.f) override;
			void DestroySelf();

		};
	}
}