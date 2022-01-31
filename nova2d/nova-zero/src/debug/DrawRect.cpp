#pragma once
#include "DrawRect.h"
#include "../graphics/Drawable.h"
#include "../core/Game.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;

		DrawRect::DrawRect(std::string fillColor, std::string outlineColor,
			bool filled, Rect rect, int outlineThickness, char layer)
			: Drawable(), Deleteable("rect_")
		{
			m_DeleteName = "rect_" + std::to_string(m_ID);

			m_FillColor = fillColor;
			m_OutlineColor = outlineColor;
			m_Filled = filled;

			SetPosition(Vec2Int(rect.x, rect.y));

			m_Outline = new SDL_Rect();
			m_Fill = new SDL_Rect();

			m_Outline->x = rect.x;
			m_Outline->y = rect.y;
			m_Outline->w = rect.w;
			m_Outline->h = rect.h;

			m_Fill->x = rect.x + outlineThickness;
			m_Fill->y = rect.y + outlineThickness;
			m_Fill->w = rect.w - 2 * outlineThickness;
			m_Fill->h = rect.h - 2 * outlineThickness;

			n2dAddDrawable(this, layer);

		};

		void DrawRect::DestroySelf()
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			CleanUpdaters();

			SetDeleted(true);
		}

		void DrawRect::Draw()
		{
			Uint8 r, g, b, a;
			SDL_GetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), &r, &g, &b, &a);

			if (m_Filled)
			{
				if (!m_Fill)
				{
					LOG(LVL_WARNING, "Cannot draw rect");
					return;
				}

				n2dRenderDrawColor(m_FillColor);
				SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Fill);
				n2dRenderDrawColor(m_OutlineColor);
				SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Outline);
			}
			else
			{
				if (!m_Outline)
				{
					LOG(LVL_WARNING, "Cannot draw rect");
					return;
				}

				n2dRenderDrawColor(m_OutlineColor);
				SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Outline);
			}

			SDL_SetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), r, g, b, a);
		}
	}
}