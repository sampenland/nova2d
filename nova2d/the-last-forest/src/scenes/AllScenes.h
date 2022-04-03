#pragma once
#include "../Enums.h"
#include "../placements/Placement.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace placements;

		class AllScenes
		{

		public:

			static Placement* s_Placements[81];

			static void NewGame();

			static void SetPlacementAt(Placement* placement, unsigned int gridPosition);
			static Placement* GetPlacementAt(unsigned int gridPosition);

			static int GetTileFromPosition(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetTopLeftOfGridCell(
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetPositionFromTile(unsigned int gridPosition, unsigned int columns);

			static Vec2 SnapToGrid(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static GridTypes GetGridTypeFromStep(unsigned int gridPosition, Facing step);
			static int GetGridPositionFromStep(unsigned int gridPosition, Facing step);

			static GridTypes GetGridPositionType(unsigned int gridPosition);
		};
	}
}