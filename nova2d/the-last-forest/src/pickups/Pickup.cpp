#include "Pickup.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace novazero::components;
		using namespace novazero::core;

		Pickup::Pickup(float delayTime)
			: m_DelayTime(delayTime)
		{
			m_DelayDisplay = new SimpleStatBar(false, 0, 0 + 78, 142, 10,
				"purple", "purple", "dark-blue", 2);
			m_DelayDisplay->SetMaxWidth(142);
			
			SetVisible(false);
		}

		void Pickup::SetVisible(bool isVisible)
		{
			m_DelayDisplay->SetVisible(isVisible);
		}

		void Pickup::Update(Vec2 position)
		{
			if (m_DelayTimer)
			{
				m_DelayDisplay->Update((m_DelayTimer->GetTimeLeft() / m_DelayTime) * 142, 
					position.x - 35.5f, position.y + 78);
			}
		}

		void Pickup::DestroySelf()
		{
			if (m_DelayDisplay)
				m_DelayDisplay->DestroySelf();

			if (m_DelayTimer)
				m_DelayTimer->DestroySelf();
		}
	}
}