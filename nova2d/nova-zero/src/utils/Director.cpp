#include "Director.h"
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		Director::Director(Vec2Int position) : Drawable(), Deleteable("director")
		{
			m_ID = n2dGameGetID();
			m_Layer = 255;

			n2dAddDrawable(this, m_Layer);

			m_Position = position;

			int x = position.x;
			int y = position.y;

			m_Background = new DrawRect("a20-blue", "white", true,
				Rect(x, y, m_Width, m_Height), 2, m_Layer);

			int padding = 10;
 			m_Title = new Text("font1", "Director", "white", Rect((float)x + padding, (float)y + padding, 100.f, 30.f), m_Layer);

			m_ScrollTime = new ScrollSelect("Time Scale", 100, "white", (float)m_Width, 40.f, 0.f, 4.f, &n2dTimeScale,
				Rect((float)x + padding, (float)m_Height - 40.f, (float)m_Width - 2 * padding, 40.f), "light-blue", "white", m_Layer);

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

			n2dPauseGame(m_Visible);

		}

		void Director::Draw(float oX, float oY)
		{

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