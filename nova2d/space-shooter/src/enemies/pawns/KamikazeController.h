#pragma once
#include "core/NovaInstance.h"
#include "Kamikaze.h"
#include "../../Player.h"
#include <vector>

namespace spaceshooter
{
	using namespace novazero::core;

	class KamikazeController : public NovaInstance
	{

	private:

		Player* m_PlayerRef;
		std::vector<Kamikaze*> m_Kamikazes;

		float* m_KamikazeSpeed;

	public:

		KamikazeController(Player* player);

		void CreateKamikaze(int wave, int kamikazeCount);
		void Wave1(int kamikazeCount);

		// Nova Instance Overrides
		void CreateInstance(Vec2 position) override {};

	};
}