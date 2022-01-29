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
			bool filled, int x, int y, int radius, char layer)
			: Drawable(), Deleteable("circle_")
		{
			m_DeleteName = "circle_" + std::to_string(m_ID);

			m_FillColor = fillColor;
			m_OutlineColor = outlineColor;

			SetPosition(Vec2Int(x, y));
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
			int r = 1;
			if (m_Filled)
			{
				Color* fc = n2dGetColor(m_FillColor);
				r = filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(), GetX(), GetY(), 
					m_Radius, fc->r, fc->g, fc->b, fc->a);
			}
			else
			{
				Color* oc = n2dGetColor(m_OutlineColor);
				r = circleRGBA(Game::s_Renderer->GetSDLRenderer(), GetX(), GetY(),
					m_Radius, oc->r, oc->g, oc->b, oc->a);
			}

			if (r != 0)
			{
				LOG(LVL_WARNING, "Unable to draw circle.");
			}
		}

		DrawCircle::~DrawCircle() {};
	}
}