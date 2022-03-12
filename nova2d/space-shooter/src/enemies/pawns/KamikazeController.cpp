#include "KamikazeController.h"
#include "utils/ValueManager.h"

namespace spaceshooter
{
	using namespace novazero::utils;

	KamikazeController::KamikazeController(Player* playerRef)
	{
		m_PlayerRef = playerRef;
		m_KamikazeSpeed = n2dValueManagerAdd("kamikaze-speed", 5.f, false);
		n2dDirectorAddToStack(false, 0, "KamiSpeed", 70.f, 0.25f, 8.f, m_KamikazeSpeed);
	}

	void KamikazeController::CreateKamikaze(int wave, int kamikazeCount)
	{
		switch(wave)
		{
			case 1:
				Wave1(kamikazeCount);
				break;
		}
	}

	void KamikazeController::Wave1(int kamikazeCount)
	{
		Kamikaze* k = nullptr;

		if (kamikazeCount % 2 == 0)
		{
			k = new Kamikaze(Vec2(Game::s_Width + 32.f, m_PlayerRef->GetPosition().y + 8), m_KamikazeSpeed);
		}
		else
		{
			k = new Kamikaze(Vec2(-32.f, m_PlayerRef->GetPosition().y + 8), m_KamikazeSpeed);
		}
		
		if (k)
		{
			m_Kamikazes.push_back(k);
		}
	}

	void KamikazeController::DestroySelf()
	{
		
	}
}