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
			float width, float height, float min, float max, float* refVal,
			Rect background, std::string backgroundColor, std::string scrollColor,
			BYTE layer) : Deleteable("scrollSelect_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "scrollSelect_" + tostring(m_ID);

			m_Width = (int)width;
			m_Height = (int)height;

			m_Min = min;
			m_Max = max;
			m_Ref = *refVal;

			m_Label = new Text("font1", labelText, textColor,
				Rect(background.x, background.y - height, (float)labelWidth, height), layer);

			m_Background = new DrawRect(backgroundColor, backgroundColor, true, background, 2, layer);
			
			float total = max - min;
			float percent = *refVal / total;
			float scrollSize = width / 20;
			float scrollPosX = background.x + (percent * width) - scrollSize / 2;
			
			m_ScrollRect = new DrawRect(scrollColor, scrollColor, true,
				Rect(scrollPosX, background.y, scrollSize, height), 2, layer);

			const float labelWidths = 60.f;
			const float labelHeights = 20.f;

			m_TextMin = new Text("font3", tostring(min), textColor,
				Rect(background.x, background.y + height + 4, labelWidths, labelHeights), layer);

			m_TextVal = new Text("font3", tostring(*refVal), textColor,
				Rect(background.x + width/2 - scrollSize/2, background.y + height + 4, labelWidths, labelHeights), layer);

			m_TextMax = new Text("font3", tostring(max), textColor,
				Rect(background.x + width - labelWidths, background.y + height + 4, labelWidths, labelHeights), layer);
			m_TextMax->SetX(m_TextMax->GetX() - 15);

			auto cleanID = n2dAddUpdater(ScrollSelect::Update, this);
			m_CleanUpdaters.push_back(cleanID);

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
			float total = m_Max - m_Min;
			float percent = m_Ref / total;
			float scrollSize = m_Width / 20;
			float scrollPosX = m_Background->GetX() + (percent * m_Width) - scrollSize / 2;
			m_TextVal->SetPosition(Vec2(scrollPosX - 6, m_Background->GetY() + m_Height + 4));
		}

		void ScrollSelect::Draw(float oX, float oY)
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