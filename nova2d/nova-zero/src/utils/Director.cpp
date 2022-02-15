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

			m_Position = position;

			

		}

		void Director::Update()
		{
			if (m_Destroyed) return;

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

			SetDeleted(true);
		}
	}
}