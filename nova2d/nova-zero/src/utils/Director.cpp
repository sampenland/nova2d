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
			int padding = 10;
 			m_Title = new Text("font1", "Director", "white", Rect((float)x, (float)y, 100.f, 50.f), m_Layer);

		}

		void Director::Update()
		{
			if (m_Destroyed) return;

		}

		void Director::Toggle()
		{
			m_Visible = !m_Visible;

			m_Title->SetVisible(m_Visible);

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

			m_Title->DestroySelf();

			SetDeleted(true);
		}
	}
}