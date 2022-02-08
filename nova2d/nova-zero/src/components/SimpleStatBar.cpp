#include "SimpleStatBar.h"
#include "../core/Game.h"

namespace novazero
{
	using namespace graphics;
	using namespace core;

	namespace components
	{
		SimpleStatBar::SimpleStatBar(bool vertical, int x, int y, int w, int h, const std::string& colorOutline,
			const std::string& colorBackground, const std::string& colorForeground, char layer)
			: Deleteable("statbar_")
		{

			m_ID = Game::GetNextID();
			m_DeleteName = "statbar_" + std::to_string(m_ID);
			m_Layer = layer;

			m_Outline = new SDL_Rect();
			m_Background = new SDL_Rect();
			m_Foreground = new SDL_Rect();

			m_BackgroundColor = colorBackground;
			m_OutlineColor = colorOutline;
			m_ForegroundColor = colorForeground;

			m_ForegroundColorAll = colorForeground;
			m_ForegroundColorHalf = colorForeground;
			m_ForegroundColorFourth = colorForeground;

			m_Size.x = w;
			m_Size.y = h;

			m_IsVertical = vertical;

			m_Value = vertical ? h : w;

			n2dAddDrawable(this, layer);
			auto cleanID = n2dAddDeleteable(this);
			m_CleanUpdaters.push_back(cleanID);

		}

		SimpleStatBar::~SimpleStatBar()
		{
			
		}

		void SimpleStatBar::Update(int v, int x, int y)
		{
			m_Value = v;
			m_Pos.x = x;
			m_Pos.y = y;
		}

		void SimpleStatBar::ConfigureThickness(int outlineThickness)
		{
			m_OutlineThickness = outlineThickness;
		}

		void SimpleStatBar::ConfigureNonForeground(int outlineThickness, const std::string& colorOutline, const std::string& colorBackground)
		{
			m_OutlineThickness = outlineThickness;
			m_OutlineColor = colorOutline;
			m_BackgroundColor = colorBackground;
		}

		void SimpleStatBar::ConfigureForeground(const std::string& colorForeground, const std::string& colorForeground2, const std::string& colorForeground4)
		{
			m_ForegroundColorAll = colorForeground;
			m_ForegroundColorHalf = colorForeground2;
			m_ForegroundColorFourth = colorForeground4;
		}

		void SimpleStatBar::Draw(float oX, float oY)
		{
			m_Outline->x = m_Pos.x - m_OutlineThickness;
			m_Outline->y = m_Pos.y - m_OutlineThickness;
			m_Outline->w = m_Size.x + 2 * m_OutlineThickness;
			m_Outline->h = m_Size.y + 2 * m_OutlineThickness;

			m_Background->x = m_Pos.x;
			m_Background->y = m_Pos.y;
			m_Background->w = m_Size.x;
			m_Background->h = m_Size.y;

			m_Foreground->x = m_Pos.x;
			m_Foreground->y = m_Pos.y;

			if (m_IsVertical)
			{
				if (m_Value > m_Size.y / 2)
				{
					m_ForegroundColor = m_ForegroundColorAll;
				}
				else if (m_Value > m_Size.y / 4)
				{
					m_ForegroundColor = m_ForegroundColorHalf;
				}
				else
				{
					m_ForegroundColor = m_ForegroundColorFourth;
				}

				m_Foreground->w = m_Size.x;
				m_Foreground->h = m_Value;
			}
			else
			{
				if (m_Value > m_Size.x / 2)
				{
					m_ForegroundColor = m_ForegroundColorAll;
				}
				else if (m_Value > m_Size.x / 4)
				{
					m_ForegroundColor = m_ForegroundColorHalf;
				}
				else
				{
					m_ForegroundColor = m_ForegroundColorFourth;
				}

				m_Foreground->w = m_Value;
				m_Foreground->h = m_Size.y;
			}

			Uint8 r, g, b, a;
			SDL_GetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), &r, &g, &b, &a);
			
			n2dRenderDrawColor(m_OutlineColor);
			SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Outline);
			n2dRenderDrawColor(m_BackgroundColor);
			SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Background);
			n2dRenderDrawColor(m_ForegroundColor);
			SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Foreground);

			SDL_SetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), r, g, b, a);
		}

		void SimpleStatBar::DestroySelf()
		{
			if (m_Foreground)
				delete m_Foreground;

			if (m_Outline)
				delete m_Outline;

			if (m_Background)
				delete m_Background;

			CleanUpdaters();

			n2dRemoveDrawable(m_ID, m_Layer);

			SetDeleted(true);
		}
	}
}