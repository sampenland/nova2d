#include "HumanController.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace scenes;
	
		HumanController::HumanController()
		{
		}

		void HumanController::CreateHuman(int count)
		{

			int col = n2dRandomInt(1, 7);
			std::vector<int> searched;

			while (searched.size() < 7)
			{
				if (!AllScenes::HumanOnColumn(col))
				{
					break;
				}

				for (size_t i = 0; i < searched.size(); i++)
				{
					if (searched[i] == col)
					{
						continue;
					}
				}

				searched.push_back(col);
			}

			if (searched.size() == 7) return;

			float humanX = col * 142 + 1 + 142 / 2 - 71 / 2;
			float humanY = -80;

			AllScenes::SetHumanOnColumn(col, true);
			Human* human = new Human(Vec2(humanX, humanY), Vec2Int(71, 70), 0);

			m_Humans.push_back(human);

		}
	}
}