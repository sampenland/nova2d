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

			int resource = n2dRandomInt(1, 10);
			if (resource > 8) // 20 percent heart
			{
				Heart* heart = new Heart(row);
			}
			else if (resource > 4) // 40 percent water
			{
				Water* water = new Water(row);
			}
			else // 40 percent sun
			{
				Sun* sun = new Sun(row);
			}
		}
	}
}