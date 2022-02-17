#include "Director.h"
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		// ----------------------------
		BYTE Director::s_CurrentPage = 0;
		std::vector<DirectorPage*> Director::s_Pages;

		Director::Director(Vec2Int position) : Drawable(), Deleteable("director")
		{
			m_ID = n2dGameGetID();
			m_Layer = 255;

			n2dAddDrawable(this, m_Layer);

			for(int i = 0; i < MAX_DIRECTOR_PAGES; i++)
				s_Pages.push_back(new DirectorPage());

			m_Position = position;

			int x = position.x;
			int y = position.y + 10;

			m_Background = new DrawRect("a20-blue", "white", true,
				Rect(x, y, m_Width, m_Height), 2, m_Layer);

			int padding = 10;
 			m_Title = new Text("font1", "Director", "white", Rect((float)x + padding, (float)y + padding - 45.f, 100.f, 30.f), m_Layer);

			m_ScrollTime = new ScrollSelect("Time Scale", 60, "white", (float)m_Width - m_Title->GetWidth(), 20.f, 0.f, 4.f, &Game::s_TimeScaleMemory,
				Rect((float)x + padding, (float)y + padding + 15.f, (float)m_Width + padding, 30.f), "light-blue", "white", m_Layer, true);

			m_ScrollTime->Select(true, "bright-blue", "white");
			m_ScrollTime->SetValueColor("purple");

			m_Visible = true;
			Toggle();

		}

		void Director::Update()
		{
			if (m_Destroyed) return;
		}

		void Director::Toggle()
		{
			m_Visible = !m_Visible;

			m_Background->SetVisible(m_Visible);
			m_Title->SetVisible(m_Visible);
			m_ScrollTime->SetVisible(m_Visible);

			m_Background->SetEnabled(m_Visible);
			m_Title->SetEnabled(m_Visible);
			m_ScrollTime->SetEnabled(m_Visible);

			for (size_t i = 0; i < s_Pages.size(); i++)
			{
				for (size_t l = 0; l < s_Pages[i]->m_LeftStack.size(); l++)
				{
					s_Pages[i]->m_LeftStack[l]->SetVisible(m_Visible);
					s_Pages[i]->m_LeftStack[l]->SetEnabled(m_Visible);
				}

				for (size_t r = 0; r < s_Pages[i]->m_RightStack.size(); r++)
				{
					s_Pages[i]->m_RightStack[r]->SetVisible(m_Visible);
					s_Pages[i]->m_RightStack[r]->SetEnabled(m_Visible);
				}
			}

			n2dPauseGame(m_Visible);

		}

		void Director::Draw(float oX, float oY)
		{

		}

		void Director::AddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float min, float max, float* refVal)
		{
			if (page < 0) page = 0;
			if (page > MAX_DIRECTOR_PAGES) page = MAX_DIRECTOR_PAGES;

			const int currentLeftSize = s_Pages.at(page)->m_LeftStack.size();
			const int currentRightSize = s_Pages.at(page)->m_RightStack.size();
			
			if (left && currentLeftSize >= 5)
			{
				if (page != MAX_DIRECTOR_PAGES)
				{
					page++;
					LOG(LVL_I, "Could not place " + labelText + 
						" on Director Page [" + tostring(page) + "]. Added to next page.");
				}
				else
				{
					LOG(LVL_W, "Ran out of space to place: " + labelText + " on Director LEFT stack");
					return;
				}
			}
			else if(!left && currentRightSize)
			{
				if (page != MAX_DIRECTOR_PAGES)
				{
					page++;
					LOG(LVL_I, "Could not place " + labelText +
						" on Director Page [" + tostring(page) + "]. Added to next page.");
				}
				else
				{
					LOG(LVL_W, "Ran out of space to place: " + labelText + " on Director RIGHT stack");
					return;
				}
			}

			if (left)
			{
				float x = s_LeftStackX;
				float y = s_StackStartY + currentLeftSize * 50.f;

				ScrollSelect* selector = new ScrollSelect(labelText, labelWidth, "white", 150.f, 14.f, min, max, refVal,
					Rect(x, y, 180.f, 30.f), "light-blue", "white", 255, true);
				
				selector->SetValueColor("purple");
				selector->SetVisible(false);
				selector->SetEnabled(false);
				
				s_Pages.at(page)->m_LeftStack.push_back(selector);
			}
			else
			{		
				float x = s_RightStackX;
				float y = s_StackStartY + currentRightSize * 50.f;

				ScrollSelect* selector = new ScrollSelect(labelText, labelWidth, "white", 150.f, 14.f, min, max, refVal,
					Rect(x, y, 180.f, 30.f), "light-blue", "white", 255, true);
				
				selector->SetValueColor("purple");
				selector->SetVisible(false);
				selector->SetEnabled(false);

				s_Pages.at(page)->m_RightStack.push_back(selector);
			}
		}

		void Director::DestroySelf()
		{
			if (m_Destroyed) return;
			m_Destroyed = true;

			CleanUpdaters();

			n2dRemoveDrawable(m_ID, m_Layer);

			m_Background->DestroySelf();
			m_Title->DestroySelf();

			SetDeleted(true);
		}
	}
}