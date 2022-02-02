#pragma once
#include "DrawCircle.h"
#include "../graphics/Drawable.h"
#include "../core/Game.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;

		DrawCircle::DrawCircle(std::string fillColor, std::string outlineColor, 
			bool filled, Vec2 position, int radius, char layer)
			: Drawable(), Deleteable("circle_")
		{
			m_DeleteName = "circle_" + std::to_string(m_ID);

			m_FillColor = fillColor;
			m_OutlineColor = outlineColor;
			m_Filled = filled;

			SetPosition(position);
			m_Radius = radius;

			n2dAddDrawable(this, layer);

		};

		void DrawCircle::DestroySelf()
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			CleanUpdaters();

			SetDeleted(true);
		}

		void DrawCircle::Draw()
		{
			int x = (int)GetX();
			int y = (int)GetY();

			if (m_Radius < 1)
				m_Radius = 1;

			int r = 1;
			if (m_Filled)
			{
				Color* fc = n2dGetColor(m_FillColor);
				r = filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(), x, y, 
					m_Radius, fc->r, fc->g, fc->b, fc->a);
			}
			else
			{
				Color* oc = n2dGetColor(m_OutlineColor);
				r = circleRGBA(Game::s_Renderer->GetSDLRenderer(), x, y,
					m_Radius, oc->r, oc->g, oc->b, oc->a);
			}

			if (r != 0)
			{
				LOG(LVL_WARNING, "Unable to draw circle.");
			}
		}
	}
}