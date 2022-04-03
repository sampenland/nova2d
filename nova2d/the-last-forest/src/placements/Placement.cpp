#include "Placement.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace placements
	{
		using namespace novazero::graphics;
		using namespace scenes;

		Placement::Placement(GridTypes type, unsigned int humanDelay,
			unsigned int gridPos, Vec2Int size, unsigned char layer)
		{
			
			std::string assetName = "";
			switch (type)
			{
			case GridTypes::Free:
				assetName = "error";
				break;
			case GridTypes::PTree:
				break;
			case GridTypes::DeadPTree:
				break;
			case GridTypes::Tree:
				assetName = "tree";
				break;
			case GridTypes::Grass:
				break;
			case GridTypes::Water:
				break;
			case GridTypes::Sun:
				break;
			}

			Vec2 position = AllScenes::GetPositionFromTile(gridPos, 9);
			position.x += 35.5f;
			position.y += 4.f;

			AddSprite(assetName, position, size, layer);
			ConfigureCollider(GetSprite(), 0, "tree");

			AllScenes::SetGridPosition(gridPos, type);

		}
	}
}