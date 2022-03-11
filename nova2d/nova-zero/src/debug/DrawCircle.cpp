#pragma once
#include "DrawCircle.h"
#include "../graphics/Drawable.h"
#include "../core/Game.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;

		DrawCircle::DrawCircle(const std::string& fillColor, const std::string& outlineColor,
			bool filled, Vec2Int position, int radius, char layer)
			: Drawable(Vec2Int(radius, radius)), Deleteable("circle_")
		{
			m_DeleteName = "circle_" + std::to_string(m_ID);

			m_FillColor = fillColor;
			m_OutlineColor = outlineColor;
			m_Filled = filled;

			SetPositionInt(position);
			m_Radius = radius;

			n2dAddDrawable(this, layer);

		};

		void DrawCircle::DestroySelf()
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			CleanUpdaters();

			SetDeleted(true);
		}

		void DrawCircle::Draw(float oX, float oY, float zoom)
		{
			if (!m_Visible) return;

			int x = (int)GetX();
			int y = (int)GetY();

			if (m_Radius < 1.f)
			{
				m_Radius = 2;
				LOG(LVL_WARNING, "Circle radius too small. Defaulting to 2.");
			}

			int r = 1;
			if (m_Filled)
			{
				Color* fc = n2dGetColor(m_FillColor);
				r = filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(), x, y, 
					(int)m_Radius, fc->r, fc->g, fc->b, fc->a);
			}
			else
			{
				Color* oc = n2dGetColor(m_OutlineColor);
				r = circleRGBA(Game::s_Renderer->GetSDLRenderer(), x, y,
					(int)m_Radius, oc->r, oc->g, oc->b, oc->a);
			}

			if (r != 0)
			{
				LOG(LVL_WARNING, "Unable to draw circle.");
			}
		}
	}
}