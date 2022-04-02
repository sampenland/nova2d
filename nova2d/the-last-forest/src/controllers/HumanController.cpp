#include "HumanController.h"

namespace thelastforest
{
	namespace controllers
	{
		HumanController::HumanController()
		{
		}

		void HumanController::CreateHuman(int col)
		{
			float humanX = col * 142 + 1 + 142 / 2 - 71 / 2;
			float humanY = -80;

			Human* human = new Human(Vec2(humanX, humanY), Vec2Int(71, 70), 0);

			m_Humans.push_back(human);

		}
	}
}