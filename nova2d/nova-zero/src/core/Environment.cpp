#include "Environment.h"
#include "../core/Game.h"

namespace novazero
{
	namespace core
	{
		using namespace novazero::debug;

		Environment::Environment(Uint8 intensity)
			: Drawable(Vec2Int(1280, 800))
		{
			m_WorldLight.x = 0;
			m_WorldLight.y = 0;

			m_WorldLight.w = Game::s_Width;
			m_WorldLight.h = Game::s_Height;

			m_WorldLightingIntensity = new Uint8;
			(*m_WorldLightingIntensity) = intensity;

			m_WorldLightingColor = new Color(0, 0, 0, *m_WorldLightingIntensity);

			n2dAddDrawable(this, TOP_DRAW_LAYER);
		}

		void Environment::Draw(float oX, float oY, float scale)
		{
			SDL_SetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(),
				m_WorldLightingColor->r, m_WorldLightingColor->g, 
				m_WorldLightingColor->b, 255 - (*m_WorldLightingIntensity));

			SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), &m_WorldLight);

		}

		void Environment::DestroySelf()
		{
			if (m_WorldLightingIntensity)
				delete m_WorldLightingIntensity;

		}
	}
}