#include "ResourceController.h"
#include "../scenes/AllScenes.h"
#include "../GameDesigner.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace scenes;
		using namespace pickups;

		ResourceController::ResourceController()
		{
		}

		void ResourceController::CreateResource()
		{

			if (m_Resources >= g_LevelOneTrees) return;
			m_Resources++;

			int row = n2dRandomInt(1, 7);
			bool isSun = n2dCoinFlip();

			std::vector<int> searched;

			while (searched.size() < 7)
			{
				if (!AllScenes::ResourceOnRow(row))
				{
					break;
				}

				for (size_t i = 0; i < searched.size(); i++)
				{
					if (searched[i] == row)
					{
						continue;
					}
				}

				searched.push_back(row);
			}

			if (searched.size() == 7) return;

			AllScenes::SetResourceOnRow(row, true);

			if (isSun)
			{
				Sun* sun = new Sun(row);
			}
			else
			{
				Water* water = new Water(row);
			}
		}
	}
}