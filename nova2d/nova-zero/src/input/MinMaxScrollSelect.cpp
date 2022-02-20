#include "MinMaxScrollSelect.h"
#include "../core/Game.h"

namespace novazero
{
	namespace input
	{
		using namespace core;
		using namespace graphics;
		using namespace debug;

		MinMaxScrollSelect::MinMaxScrollSelect(
			std::string labelText, int labelWidth, std::string textColor,
			float width, float height, float inOrDecreaseBy, float min, float max, float* minRefVal, float* maxRefVal,
			Rect background, std::string backgroundColor, std::string scrollColor,
			BYTE layer, bool isPersistent) : Deleteable("minMaxScrollSelect_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "minMaxScrollSelect_" + tostring(m_ID);

			m_Width = (int)width;
			m_Height = (int)background.h;

			m_InOrDecreaseBy = inOrDecreaseBy;
			m_Min = min;
			m_Max = max;
			m_MinRef = minRefVal;
			m_MaxRef = maxRefVal;

			m_Position = Vec2Int((int)background.x, (int)background.y);

			m_Label = new Text("narrow", labelText, textColor,
				Rect(background.x, background.y - height * 1.5, (float)labelWidth, height * 1.5), layer);

			float scrollSize = (float)m_Width / 10;
			float percentMin = *m_MinRef / m_Max;
			float percentMax = *m_MaxRef / m_Max;

			float minScrollPosX = m_Position.x + (percentMin * m_Width);
			float maxScrollPosX = m_Position.x + (percentMax * m_Width);

			if (minScrollPosX > m_Position.x + m_Width - scrollSize / 2)
				minScrollPosX = m_Position.x + m_Width - scrollSize / 2;

			if (maxScrollPosX > m_Position.x + m_Width - scrollSize / 2)
				maxScrollPosX = m_Position.x + m_Width - scrollSize / 2;

			m_Width = (int)(background.w - scrollSize + 10);
			m_Background = new DrawRect(backgroundColor, backgroundColor, true,
				Rect(background.x, background.y, (float)m_Width, background.h), 2, layer);

			m_MinScrollRect = new DrawRect(scrollColor, scrollColor, true,
				Rect(minScrollPosX, background.y, scrollSize, background.h), 2, layer);

			m_MaxScrollRect = new DrawRect(scrollColor, scrollColor, true,
				Rect(maxScrollPosX, background.y, scrollSize, background.h), 2, layer);

			m_MinScrollRect->SetColors("white", "white");
			m_MaxScrollRect->SetColors("light-blue", "light-blue");

			const float labelWidths = 60.f;
			const float labelHeights = 20.f;

			m_TextMin = new Text("narrow", "0.0", textColor,
				Rect(background.x, background.y + background.h + 4, labelWidths, labelHeights), layer);

			m_TextMinVal = new Text("narrow", tostring(*m_MinRef), textColor,
				Rect(background.x + width / 2 - scrollSize / 2, background.y + background.h + 4, labelWidths, labelHeights), layer);

			m_TextMaxVal = new Text("narrow", tostring(*m_MaxRef), textColor,
				Rect(background.x + width / 2 - scrollSize / 2, background.y + background.h + 4, labelWidths, labelHeights), layer);

			m_TextMax = new Text("narrow", tostring(max), textColor,
				Rect(background.x + width - labelWidths, background.y + background.h + 4, labelWidths, labelHeights), layer);
			m_TextMax->SetX(background.x + m_Width - labelWidths);

			m_TextMinVal->UpdateText(tostring(*m_MinRef), Vec2Int((int)minScrollPosX - 10, (int)m_Background->GetY() + 4));
			m_TextMaxVal->UpdateText(tostring(*m_MaxRef), Vec2Int((int)maxScrollPosX - 10, (int)m_Background->GetY() + 4));

			if (isPersistent)
			{
				auto cleanID = n2dAddUpdaterPersistent(MinMaxScrollSelect::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}
			else
			{
				auto cleanID = n2dAddUpdater(MinMaxScrollSelect::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}
		}

		void MinMaxScrollSelect::SetVisible(bool isVisible)
		{
			m_Label->SetVisible(isVisible);
			m_Background->SetVisible(isVisible);
			m_MinScrollRect->SetVisible(isVisible);
			m_MaxScrollRect->SetVisible(isVisible);

			m_TextMin->SetVisible(isVisible);
			m_TextMinVal->SetVisible(isVisible);
			m_TextMaxVal->SetVisible(isVisible);
			m_TextMax->SetVisible(isVisible);
		}

		void MinMaxScrollSelect::Update()
		{
			if (!IsEnabled()) return;

			if (m_Selected)
			{
				HandleSelected();
			}
		}

		void MinMaxScrollSelect::HandleSelected()
		{
			if (!n2dIsKeyDown(SDLK_LEFT) && !n2dJoyDPadLeft(0) &&
				!n2dIsKeyDown(SDLK_RIGHT) && !n2dJoyDPadRight(0))
			{
				m_SelectionLock = false;
			}
			
			if (m_SelectionLock) return;

			if (n2dIsKeyDown(SDLK_LEFT) || n2dJoyDPadLeft(0) ||
				n2dIsKeyDown(SDLK_RIGHT) || n2dJoyDPadRight(0))
			{
				m_SelectionLock = true;
				m_MinSelected = !m_MinSelected;

				if (m_MinSelected)
				{
					m_MinScrollRect->SetColors("white", "white");
					m_MaxScrollRect->SetColors("light-blue", "light-blue");
				}
				else
				{
					m_MinScrollRect->SetColors("light-blue", "light-blue");
					m_MaxScrollRect->SetColors("white", "white");
				}
			}

			HandleValueChanging();
		}

		void MinMaxScrollSelect::HandleValueChanging()
		{
			// TODO: n2d - right joystick
			bool update = false;
			if (m_MinSelected)
			{
				if (n2dIsKeyDown(SDLK_a) || n2dJoyRSimpleLeft(0))
				{
					if (*m_MinRef > m_Min)
					{
						*m_MinRef -= m_InOrDecreaseBy;
						if (*m_MinRef < m_InOrDecreaseBy) *m_MinRef = m_Min;
						update = true;
					}
				}
				else if (n2dIsKeyDown(SDLK_d) || n2dJoyRSimpleRight(0))
				{
					if (*m_MinRef < *m_MaxRef)
					{
						*m_MinRef += m_InOrDecreaseBy;
						if (*m_MinRef > *m_MaxRef) *m_MinRef = *m_MaxRef;
						update = true;
					}
				}
			}
			else
			{
				if (n2dIsKeyDown(SDLK_a) || n2dJoyRSimpleLeft(0))
				{
					if (*m_MaxRef > *m_MinRef)
					{
						*m_MaxRef -= m_InOrDecreaseBy;
						if (*m_MaxRef < *m_MinRef) *m_MaxRef = *m_MinRef;
						update = true;
					}
				}
				else if (n2dIsKeyDown(SDLK_d) || n2dJoyRSimpleRight(0))
				{
					if (*m_MaxRef < m_Max)
					{
						*m_MaxRef += m_InOrDecreaseBy;
						if (*m_MaxRef > m_Max) *m_MaxRef = m_Max;
						update = true;
					}
				}
			}

			if (update)
			{
				float scrollSize = (float)m_Width / 20;
				float percentMin = *m_MinRef / m_Max;
				float percentMax = *m_MaxRef / m_Max;

				float minScrollPosX = m_Position.x + (percentMin * m_Width);
				float maxScrollPosX = m_Position.x + (percentMax * m_Width);

				if (maxScrollPosX > m_Position.x + m_Width - scrollSize * 1.5)
					maxScrollPosX = m_Position.x + m_Width - scrollSize * 1.5;
				
				if (minScrollPosX > maxScrollPosX)
					minScrollPosX = maxScrollPosX;

				m_TextMinVal->UpdateText(tostring(*m_MinRef), Vec2Int((int)minScrollPosX - 10, (int)m_Background->GetY() + 4));
				m_TextMaxVal->UpdateText(tostring(*m_MaxRef), Vec2Int((int)maxScrollPosX - 10, (int)m_Background->GetY() + 4));
				
				m_MinScrollRect->SetPosition(Vec2(minScrollPosX, m_MinScrollRect->GetY()));
				m_MaxScrollRect->SetPosition(Vec2(maxScrollPosX, m_MaxScrollRect->GetY()));
			}
		}

		void MinMaxScrollSelect::Select(bool isSelected, const std::string& fillColor, const std::string& outlineColor)
		{
			m_Selected = isSelected;
			m_Background->SetColors(fillColor, outlineColor);
		}

		void MinMaxScrollSelect::Draw(float oX, float oY)
		{

		}

		void MinMaxScrollSelect::DestroySelf()
		{
			if (m_Destroyed) return;
			m_Destroyed = true;

			CleanUpdaters();

			m_Label->DestroySelf();
			m_Background->DestroySelf();
			m_MinScrollRect->DestroySelf();
			m_MaxScrollRect->DestroySelf();

			m_TextMin->DestroySelf();
			m_TextMinVal->DestroySelf();
			m_TextMaxVal->DestroySelf();
			m_TextMax->DestroySelf();

			SetDeleted(true);
		}
	}
}