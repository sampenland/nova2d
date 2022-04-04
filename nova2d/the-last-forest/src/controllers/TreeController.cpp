#include "TreeController.h"
#include "../scenes/AllScenes.h"
#include "../GameDesigner.h"

namespace thelastforest
{
	namespace controllers
	{
		using namespace novazero::utils::timeline;
		using namespace pickups;
		using namespace scenes;

		TreeController::TreeController()
		{
		}

		void TreeController::CreateTree()
		{
			if (m_Trees >= g_LevelOneTrees) return;
			m_Trees++;

			int row = n2dRandomInt(1, 7);
			std::vector<int> searched;

			while (searched.size() < 7)
			{
				if (!AllScenes::TreeOnRow(row))
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

			AllScenes::SetTreeOnRow(row, true);
			Tree* tree = new Tree(row);

		}
	}
}