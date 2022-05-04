#include "ScrollSelect.h"
#include "../core/Game.h"

namespace novazero
{
	namespace input
	{
		using namespace core;
		using namespace graphics;
		using namespace debug;

		ScrollSelect::ScrollSelect(
			std::string labelText, int labelWidth, std::string textColor,
			float width, float height, float inOrDecreaseBy, float max, float* refVal,
			Rect background, std::string backgroundColor, std::string scrollColor,
			unsigned char layer, bool isPersistent) : Deleteable("scrollSelect_"), Drawable(Vec2Int((int)background.w, (int)background.h))
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "scrollSelect_" + tostring(m_ID);

			m_Width = (int)width;
			m_Height = (int)background.h;

			m_InOrDecreaseBy = inOrDecreaseBy;
			m_Max = max;
			m_Ref = refVal;

			m_Position = Vec2(background.x, background.y);

			m_Label = new Text("narrow", labelText, textColor,
				Rect(background.x, background.y - height, (float)labelWidth, height), layer);
			m_Label->SetFixedAndNonScale(true);

			float percent = *m_Ref / m_Max;
			float scrollSize = (float)m_Width / 20;
			float scrollPosX = m_Position.x + (percent * m_Width);

			if (scrollPosX > m_Position.x + m_Width - scrollSize / 2)
				scrollPosX = m_Position.x + m_Width - scrollSize / 2;
			
			m_Width = (int)(background.w - scrollSize + 10);
			m_Background = new DrawRect(backgroundColor, backgroundColor, true,
				Rect(background.x, background.y, (float)m_Width, background.h), 2, layer);
			
			m_ScrollRect = new DrawRect(scrollColor, scrollColor, true,
				Rect(scrollPosX, background.y, scrollSize, background.h), 2, layer);

			const float labelWidths = 60.f;
			const float labelHeights = 20.f;

			m_TextMin = new Text("narrow", "0.0", textColor,
				Rect(background.x, background.y + background.h + 4, labelWidths, labelHeights), layer);

			m_TextVal = new Text("narrow", tostring(*refVal), textColor,
				Rect(background.x + width/2 - scrollSize/2, background.y + background.h + 4, labelWidths, labelHeights), layer);

			m_TextMax = new Text("narrow", tostring(max), textColor,
				Rect(background.x + width - labelWidths, background.y + background.h + 4, labelWidths, labelHeights), layer);
			m_TextMax->SetX(background.x + m_Width - labelWidths);

			m_TextVal->UpdateText(tostring(*m_Ref), Vec2Int((int)scrollPosX - 10, (int)m_Background->GetY() + 4));

			m_Label->SetFixedAndNonScale(true);
			m_Background->SetFixedAndNonScale(true);
			m_ScrollRect->SetFixedAndNonScale(true);

			m_TextMin->SetFixedAndNonScale(true);
			m_TextVal->SetFixedAndNonScale(true);
			m_TextMax->SetFixedAndNonScale(true);
			m_TextVal->SetFixedAndNonScale(true);

			if (isPersistent)
			{
				auto cleanID = n2dAddUpdaterPersistent(ScrollSelect::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}
			else
			{
				auto cleanID = n2dAddUpdater(ScrollSelect::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}
		}

		void ScrollSelect::SetVisible(bool isVisible)
		{
			m_Label->SetVisible(isVisible);
			m_Background->SetVisible(isVisible);
			m_ScrollRect->SetVisible(isVisible);

			m_TextMin->SetVisible(isVisible);
			m_TextVal->SetVisible(isVisible);
			m_TextMax->SetVisible(isVisible);
		}

		void ScrollSelect::Update()
		{
			if (!IsEnabled() || !IsVisible()) return;

			if (m_Selected)
			{
				HandleSelected();
			}
		}

		void ScrollSelect::HandleSelected()
		{
			bool update = false;
			if (n2dIsKeyDown(SDLK_LEFT) || n2dJoyRSimpleLeft(0))
			{
				if (*m_Ref > m_Min)
				{
					*m_Ref -= m_InOrDecreaseBy;
					if (*m_Ref < m_InOrDecreaseBy) *m_Ref = m_Min;
					update = true;
				}
			}
			else if (n2dIsKeyDown(SDLK_RIGHT) || n2dJoyRSimpleRight(0))
			{
				if (*m_Ref < m_Max)
				{
					*m_Ref += m_InOrDecreaseBy;
					if (*m_Ref > m_Max) *m_Ref = m_Max;
					update = true;
				}
			}

			if (update)
			{
				float percent = *m_Ref / m_Max;
				float scrollSize = (float)m_Width / 20;
				float scrollPosX = m_Position.x + (percent * m_Width);
				
				if (scrollPosX > m_Position.x + m_Width - scrollSize/2)
					scrollPosX = m_Position.x + m_Width - scrollSize/2;
				
				m_TextVal->UpdateText(tostring(*m_Ref), Vec2Int((int)scrollPosX - 10, (int)m_Background->GetY() + 4));
				m_ScrollRect->SetPosition(Vec2(scrollPosX, m_ScrollRect->GetY()));
			}
		}

		void ScrollSelect::Select(bool isSelected, const std::string& fillColor, const std::string& outlineColor)
		{
			m_Selected = isSelected;
			m_Background->SetColors(fillColor, outlineColor);
		}

		void ScrollSelect::Draw(float oX, float oY, float scale)
		{

		}

		void ScrollSelect::DestroySelf()
		{
			if (m_Destroyed) return;
			m_Destroyed = true;

			CleanUpdaters();

			m_Label->DestroySelf();
			m_Background->DestroySelf();
			m_ScrollRect->DestroySelf();

			m_TextMin->DestroySelf();
			m_TextVal->DestroySelf();
			m_TextMax->DestroySelf();

			SetDeleted(true);
		}
	}
}