#include "SimpleStatBar.h"
#include "../core/Game.h"

namespace novazero
{
	using namespace graphics;
	using namespace core;

	namespace components
	{
		SimpleStatBar::SimpleStatBar(bool vertical, int x, int y, int w, int h, const std::string& colorOutline,
			const std::string& colorBackground, const std::string& colorForeground, unsigned char layer)
			: Deleteable("statbar_"), Drawable(Vec2Int(0,0))
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

			SetSize(Vec2Int(w, h));

			m_IsVertical = vertical;

			m_Value = vertical ? h : w;
			Update(m_Value, x, y);

			n2dAddDrawable(this, layer);
			auto cleanID = n2dAddDeleteable(this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void SimpleStatBar::SetMaxWidth(int w)
		{
			SetSize(Vec2Int(w, GetSize().y));
		}

		void SimpleStatBar::Update(int v, int x, int y)
		{
			m_Value = v;
			SetPositionInt(Vec2Int(x, y));
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

		void SimpleStatBar::Scale(float scale)
		{
			//m_Scale = scale;
		}

		void SimpleStatBar::Draw(float oX, float oY, float scale)
		{
			if (!IsVisible()) return;

			m_Outline->x = (int)(oX - m_OutlineThickness);
			m_Outline->y = (int)(oY - m_OutlineThickness);
			m_Outline->w = (int)(GetSize().x * scale) + 2 * m_OutlineThickness;
			m_Outline->h = (int)(GetSize().y * scale) + 2 * m_OutlineThickness;

			m_Background->x = (int)(oX);
			m_Background->y = (int)(oY);
			m_Background->w = (int)(GetSize().x * scale);
			m_Background->h = (int)(GetSize().y * scale);

			m_Foreground->x = (int)(oX);
			m_Foreground->y = (int)(oY);

			if (m_IsVertical)
			{
				if (m_Value > GetSize().y / 2)
				{
					m_ForegroundColor = m_ForegroundColorAll;
				}
				else if (m_Value > GetSize().y / 4)
				{
					m_ForegroundColor = m_ForegroundColorHalf;
				}
				else
				{
					m_ForegroundColor = m_ForegroundColorFourth;
				}

				m_Foreground->w = (int)(GetSize().x * scale);
				m_Foreground->y = (int)(oY + GetSize().y * scale);
				m_Foreground->h = (int)(-m_Value * scale);
			}
			else
			{
				if (m_Value > GetSize().x / 2)
				{
					m_ForegroundColor = m_ForegroundColorAll;
				}
				else if (m_Value > GetSize().x / 4)
				{
					m_ForegroundColor = m_ForegroundColorHalf;
				}
				else
				{
					m_ForegroundColor = m_ForegroundColorFourth;
				}

				m_Foreground->w = (int)(m_Value * scale);
				m_Foreground->h = (int)(GetSize().y * scale);
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