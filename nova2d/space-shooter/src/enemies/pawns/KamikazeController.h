#pragma once
#include "utils/timeline/TimelineInstance.h"
#include "Kamikaze.h"
#include "../../Player.h"
#include <vector>

namespace spaceshooter
{
	using namespace novazero::core;

	class KamikazeController : public TimelineInstance
	{

	private:

		Player* m_PlayerRef;
		std::vector<Kamikaze*> m_Kamikazes;

		float* m_KamikazeSpeed;

	public:

		KamikazeController(Player* player);

		void CreateKamikaze(int wave, int kamikazeCount);
		void Wave1(int kamikazeCount);

		void DestroySelf();

	};
}