#include "TextInput.h"
#include "../core/Game.h"

namespace novazero
{
	namespace input
	{
		TextInput::TextInput(const std::string& fontName, const std::string& placeholderText, const std::string& textColorName, 
			const std::string& backgroundColorName, Rect drawRect,
			char layer) : Deleteable("textinput"), Drawable(Vec2Int((int)drawRect.w, (int)drawRect.h))
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "textinput_" + std::to_string(m_ID);

			m_Layer = layer;
			m_DisplayText = new Text(fontName, placeholderText, textColorName, drawRect, layer, false);

			m_BackgroundColor = backgroundColorName;

			m_Background = new SDL_Rect();
			m_Background->x = (int)drawRect.x;
			m_Background->y = (int)drawRect.y;
			m_Background->w = (int)drawRect.w;
			m_Background->h = (int)drawRect.h;

			n2dAddDrawable(this, m_Layer);

			auto cleanID = n2dAddUpdater(TextInput::Update, this);
			m_CleanUpdaters.push_back(cleanID);			

		};

		void TextInput::Configure(bool startSelected, int maxChars)
		{
			m_MaxChars = maxChars;
			m_DisplayText->SetDynamicWithCharMax(maxChars);

			if (startSelected)
			{
				Select(true, true);
			}
		}

		void TextInput::Select(bool isSelected, bool reset)
		{
			m_Selected = isSelected;

			if (reset)
			{
				n2dTextInputClearBuffer(m_MaxChars);
				
			}

			n2dTextInputSetBuffer(m_DisplayText->GetText(), m_MaxChars);

			if (isSelected)
			{
				Game::s_InputHandler->SelectInputTarget(this);

				int index = (int)m_DisplayText->GetText().length();
				Game::s_InputHandler->SetTextBufferIndex(index);
			}
			else
			{
				Game::s_InputHandler->ClearInputTarget();
			}
		}

		void TextInput::Update()
		{
			if (m_Selected)
			{
				std::string bufferText;
				Game::s_InputHandler->GetCharBufferAsString(bufferText);

				if (bufferText != m_DisplayText->GetText())
				{
					m_DisplayText->UpdateText(bufferText);
				}
			}
		}

		void TextInput::Draw(float oX, float oY, float zoom)
		{
			Uint8 r, g, b, a;
			SDL_GetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), &r, &g, &b, &a);

			n2dRenderDrawColor(m_BackgroundColor);
			float tX = 0.f;
			float tY = 0.f;
			tX = (float)m_Background->x;
			tY = (float)m_Background->y;
			m_Background->x += (int)oX;
			m_Background->y += (int)oY;

			int w = m_Background->w;
			int h = m_Background->h;

			m_Background->w = (int)(w * zoom);
			m_Background->h = (int)(h * zoom);

			SDL_RenderFillRect(Game::s_Renderer->GetSDLRenderer(), m_Background);
			SDL_SetRenderDrawColor(Game::s_Renderer->GetSDLRenderer(), r, g, b, a);

			if (m_DisplayText)
			{
				m_DisplayText->Draw(oX, oY, zoom);
			}

			m_Background->x = (int)tX;
			m_Background->y = (int)tY;

			m_Background->w = w;
			m_Background->h = h;
		}

		void TextInput::DestroySelf()
		{
			CleanUpdaters();
			n2dRemoveDrawable(m_ID, m_Layer);

			if (m_DisplayText)
				m_DisplayText->DestroySelf();

			SetDeleted(true);
		}
	}
}