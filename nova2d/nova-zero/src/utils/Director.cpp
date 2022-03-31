#include "Director.h"
#include "../core/Game.h"
#include "../input/MinMaxScrollSelect.h"

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
		const float Director::s_StackPadding = 80.f;

		Director::Director(Vec2Int position) : Drawable(Vec2Int(0,0)), Deleteable("director")
		{
			m_ID = n2dGameGetID();
			m_Layer = PERSISTENT_LAYER;

			n2dAddDrawable(this, m_Layer);

			for(int i = 0; i < MAX_DIRECTOR_PAGES; i++)
				s_Pages.push_back(new DirectorPage());

			m_Position = position;

			int x = position.x;
			int y = position.y + 10;

			SetFixedAndNonScale(true);

			m_Background = new DrawRect("a20-blue", "white", true,
				Rect(x, y, m_Width, m_Height), 2, PERSISTENT_LAYER);

			m_MiddleScreen = new DrawRect("white", "white", false,
				Rect(Game::GetCenterScreenInt().x - 8, Game::GetCenterScreenInt().y - 8, 16, 16), 2, PERSISTENT_LAYER);
			
			m_MiddleScreenText = new Text("narrow", "", "white", 
				Rect(
					Game::GetCenterScreenInt().x - 128, 
					Game::GetCenterScreenInt().y - 64, 256, 32),
				PERSISTENT_LAYER);
			
			m_MiddleScreenTextCamera = new Text("narrow", "", "white",
				Rect(
					Game::GetCenterScreenInt().x - 128, 
					Game::GetCenterScreenInt().y + 32, 256, 32),
				PERSISTENT_LAYER);

			int padding = 10;
 			m_Title = new Text("font1", "Director", "white", Rect((float)x + padding, (float)y + padding - 45.f, 300.f, 30.f), PERSISTENT_LAYER);

			m_ScrollTime = new ScrollSelect("Time Scale", 60, "white", (float)m_Width - m_Title->GetWidth(), 20.f, 0.01f, 4.f, &Game::s_TimeScaleMemory,
				Rect((float)x + padding, (float)y + padding + 15.f, (float)m_Width + padding, 30.f), "light-blue", "white", PERSISTENT_LAYER, true);

			m_Background->SetFixedAndNonScale(true);
			m_MiddleScreen->SetFixedAndNonScale(true);
			m_MiddleScreenText->SetFixedAndNonScale(true);
			m_MiddleScreenTextCamera->SetFixedAndNonScale(true);
			m_Title->SetFixedAndNonScale(true);
			m_ScrollTime->SetFixedAndNonScale(true);

			m_ScrollTime->Select(true, "bright-blue", "white");
			m_ScrollTime->SetValueColor("purple");

			m_Visible = true;
			Toggle();

			auto cleanID = n2dAddUpdaterPersistent(Director::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void Director::Update()
		{
			if (m_Destroyed) return;

			if (!m_Visible)
			{
				m_CameraFreeMoveMemory = CAMERA->IsFreeMoveEnabled();
				m_CameraZoomLevelMemory = CAMERA_ZOOM;
			}
			else
			{
				Vec2 cameraWorldCenter = CAMERA->GetDrawRectCenter();
				m_MiddleScreenText->UpdateText("Cntr:[" + tostring((int)cameraWorldCenter.x) + ", " + tostring((int)cameraWorldCenter.y) + "]");
				
				int camPosX = (int)CAMERA->GetX();
				int camPosY = (int)CAMERA->GetY();
				m_MiddleScreenTextCamera->UpdateText("Cam:[" + tostring(camPosX) + ", " + tostring(camPosY) + "]\n Z:[" + tostring(CAMERA_ZOOM) + "]");
			}

			if (!IsEnabled()) return;

			if (n2dIsKeyUp(SDLK_UP) && 
				n2dIsKeyUp(SDLK_DOWN) && 
				!n2dJoyDPadUp(0) &&
				!n2dJoyDPadDown(0))
			{
				m_SelectionLock = false;
			}

			if (m_SelectionLock) return;

			// restart scene with Y button
			if (m_Visible && n2dIsJoyKeyDown(0, SDL_CONTROLLER_BUTTON_Y) &&
				Game::s_SceneManager->m_CurrentSceneName != "none")
			{
				Toggle();
				Game::s_SceneManager->ChangeScene(Game::s_SceneManager->m_CurrentSceneName);
				return;
			}
			// move back a scene on Left bumper
			else if (m_Visible && n2dIsJoyKeyDown(0, SDL_CONTROLLER_BUTTON_BACK) &&
				Game::s_SceneManager->m_LastSceneName != "none")
			{
				Toggle();
				Game::s_SceneManager->ChangeScene(Game::s_SceneManager->m_LastSceneName);
				return;
			}
			//TODO: move to next scene - how do we know what's next?

			const size_t leftCount = s_Pages[s_CurrentPage]->m_LeftStack.size();
			const size_t rightCount = s_Pages[s_CurrentPage]->m_RightStack.size();

			bool selectNew = false;
			DirectorStackable* currentSelected = m_ScrollTime;

			if (n2dIsKeyDown(SDLK_UP) || n2dJoyDPadUp(0))
			{
				m_SelectionLock = true;

				if (m_CurrentSelected != -1)
				{
					if (m_LeftSelectedStack)
					{
						currentSelected = s_Pages[s_CurrentPage]->m_LeftStack.at(m_CurrentSelected);
					}
					else
					{
						currentSelected = s_Pages[s_CurrentPage]->m_RightStack.at(m_CurrentSelected);
					}
				}			

				if (m_LeftSelectedStack)
				{
					if (m_CurrentSelected > -1 && leftCount > (size_t)0)
					{
						m_CurrentSelected--;
						selectNew = true;
					}
					else
					{
						return;
					}
				}
				else
				{
					if (m_CurrentSelected <= 0)
					{
						m_LeftSelectedStack = true;
						m_CurrentSelected = (short)leftCount - 1;						
						selectNew = true;
					}
					else
					{
						m_CurrentSelected--;
						selectNew = true;
					}
				}
			}
			else if (n2dIsKeyDown(SDLK_DOWN) || n2dJoyDPadDown(0))
			{
				m_SelectionLock = true;

				if (m_CurrentSelected != -1)
				{
					if (m_LeftSelectedStack)
					{
						currentSelected = s_Pages[s_CurrentPage]->m_LeftStack.at(m_CurrentSelected);
					}
					else
					{
						currentSelected = s_Pages[s_CurrentPage]->m_RightStack.at(m_CurrentSelected);
					}
				}

				if (m_LeftSelectedStack)
				{
					if (leftCount != 0)
					{
						if ((size_t)m_CurrentSelected == -1 && leftCount > 0)
						{
							m_CurrentSelected = 0;
							selectNew = true;
						}
						else if ((size_t)m_CurrentSelected < leftCount - 1)
						{
							m_CurrentSelected++;
							selectNew = true;
						}
						else if(rightCount > (size_t)0)
						{
							m_CurrentSelected = 0;
							m_LeftSelectedStack = false;
							selectNew = true;
						}
					}
					else
					{
						if (rightCount > (size_t)0)
						{
							m_LeftSelectedStack = false;
							m_CurrentSelected = 0;
							selectNew = rightCount > 0;
						}
					}
				}
				else
				{
					if (rightCount != (size_t)0)
					{
						if (m_CurrentSelected < (short)rightCount - 1)
						{
							m_CurrentSelected++;
							selectNew = true;
						}
					}
				}
			}

			if (selectNew)
			{
				ChangeSelection(currentSelected);
			}
		}

		void Director::ChangeSelection(DirectorStackable* oldSelected)
		{
			if(oldSelected)
				oldSelected->Select(false, "light-blue", "white");

			if (m_CurrentSelected == -1)
			{
				m_ScrollTime->Select(true, "bright-blue", "white");
				return;
			}

			if (m_LeftSelectedStack)
			{
				s_Pages[s_CurrentPage]->m_LeftStack.at(m_CurrentSelected)->Select(true, "bright-blue", "white");
			}
			else
			{
				s_Pages[s_CurrentPage]->m_RightStack.at(m_CurrentSelected)->Select(true, "bright-blue", "white");
			}
		}

		void Director::Toggle()
		{
			m_Visible = !m_Visible;

			SetEnabled(m_Visible);

			m_Background->SetVisible(m_Visible);
			m_MiddleScreen->SetVisible(m_Visible);
			m_MiddleScreenText->SetVisible(m_Visible);
			m_MiddleScreenTextCamera->SetVisible(m_Visible);
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

			CAMERA->EnableFreeWASDMove(m_Visible);
			if (!m_Visible)
			{
				CAMERA->EnableFreeWASDMove(m_CameraFreeMoveMemory);
				CAMERA->SetZoom(m_CameraZoomLevelMemory);
			}			
		}

		void Director::ClearStacksAndReset(bool left, bool right)
		{
			for (size_t i = 0; i < s_Pages.size(); i++)
			{
				if (left)
				{
					std::vector<DirectorStackable*>::iterator it = s_Pages[i]->m_LeftStack.begin();
					while (it != s_Pages[i]->m_LeftStack.end())
					{
						it = s_Pages[i]->m_LeftStack.erase(it);
					}
				}
				
				if (right)
				{
					std::vector<DirectorStackable*>::iterator it = s_Pages[i]->m_RightStack.begin();
					while (it != s_Pages[i]->m_RightStack.end())
					{
						it = s_Pages[i]->m_RightStack.erase(it);
					}
				}
			}

			m_LeftSelectedStack = true;
			m_CurrentSelected = -1;
			ChangeSelection(nullptr);
		}

		void Director::Draw(float oX, float oY, float scale)
		{

		}

		void Director::AddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float inOrDecreaseby, float max, float* refVal)
		{
			if (page < 0) page = 0;
			if (page > MAX_DIRECTOR_PAGES) page = MAX_DIRECTOR_PAGES;

			const int currentLeftSize = s_Pages.at(page)->m_LeftStack.size();
			const int currentRightSize = s_Pages.at(page)->m_RightStack.size();
			
			if (left && currentLeftSize >= MAX_DIRECTOR_SLOTS)
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
			else if(!left && currentRightSize >= MAX_DIRECTOR_SLOTS)
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
				float y = s_StackStartY + currentLeftSize * s_StackPadding;

				ScrollSelect* selector = new ScrollSelect(labelText, labelWidth, "white", 150.f, 14.f, inOrDecreaseby, max, refVal,
					Rect(x, y, 180.f, 30.f), "light-blue", "white", 255, true);
				
				selector->SetValueColor("purple");
				selector->SetVisible(false);
				selector->SetEnabled(false);
				
				s_Pages.at(page)->m_LeftStack.push_back(selector);
			}
			else
			{		
				float x = s_RightStackX;
				float y = s_StackStartY + currentRightSize * s_StackPadding;

				ScrollSelect* selector = new ScrollSelect(labelText, labelWidth, "white", 150.f, 14.f, inOrDecreaseby, max, refVal,
					Rect(x, y, 180.f, 30.f), "light-blue", "white", 255, true);
				
				selector->SetValueColor("purple");
				selector->SetVisible(false);
				selector->SetEnabled(false);

				s_Pages.at(page)->m_RightStack.push_back(selector);
			}
		}

		void Director::AddToStackMinMax(bool left, BYTE page, std::string labelText, 
			int labelWidth, float inOrDecreaseby, float min, float max, float* minRefVal, float* maxRefVal)
		{

			if (min >= max)
			{
				min = 0;
				LOG(LVL_W, labelText + " added to stack but min > max... forcing min to 0.f");
			}

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
			else if (!left && currentRightSize)
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
				float y = s_StackStartY + currentLeftSize * s_StackPadding;

				MinMaxScrollSelect* selector = new MinMaxScrollSelect(labelText, labelWidth, "white", 150.f, 14.f, 
					inOrDecreaseby, min, max, minRefVal, maxRefVal,
					Rect(x, y, 180.f, 30.f), "light-blue", "white", 255, true);

				selector->SetValueColor("purple");
				selector->SetVisible(false);
				selector->SetEnabled(false);

				s_Pages.at(page)->m_LeftStack.push_back(selector);
			}
			else
			{
				float x = s_RightStackX;
				float y = s_StackStartY + currentRightSize * s_StackPadding;

				MinMaxScrollSelect* selector = new MinMaxScrollSelect(labelText, labelWidth, "white", 150.f, 14.f,
					inOrDecreaseby, min, max, minRefVal, maxRefVal,
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